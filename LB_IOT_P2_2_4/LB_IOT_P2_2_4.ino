// ------------------------------------------------------------
//  Author: Miguel A.Lorenzo
//  Date: 21/09/2026
//  Subject: IoT Communications Laboratory
//  Master: MSc in Electronic Engineering
//  University: University of Zaragoza EINA/UNIZAR
// ------------------------------------------------------------
/*
 * Microcontroller: ESP32 / Arduino Framework
 * OS: FreeRTOS
 * Lab Assignment: Practical Exercise 2.3 (IoT Communications Laboratory)
 * Hardware: Adafruit MPU6050 (I2C Bus: SDA=GPIO21, SCL=GPIO22), Indicator LED (GPIO23)
 *
 * Description:
 *   FreeRTOS implementation utilizing concurrent tasks and an Idle Hook.
 *   - Task 1 (task_sensor) : Periodically samples 3-axis acceleration every 100 ms via I2C.
 *   - Task 2 (task_uart)   : Transmits acceleration metrics over UART every 1000 ms 
 *                            and triggers an indicator LED pulse for 200 ms.
 *   - Idle Hook            : Executes when the CPU has no active tasks to process.
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "esp_freertos_hooks.h"

Adafruit_MPU6050 mpu;

#define LED_PIN 23
#define TIME_SAMPLE 100
#define TIME_BLINK 200
#define TIME_PRINTER 1000

// Global variables to store acceleration values
float ax, ay, az;

// FUNCTION DECLARATIONS
bool idle_hook_function();
void task_sensor(void *parameter);
void task_uart(void *parameter);
void printer();

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  while (!Serial && millis() < 2000);

  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("Error: MPU6050 not found!");
    while (1);
  }

  // Register FreeRTOS Idle Hook
  esp_register_freertos_idle_hook(idle_hook_function);

  // Create FreeRTOS Tasks
  xTaskCreate(task_sensor, "Task_Sensor", 2048, NULL, 1, NULL);
  xTaskCreate(task_uart,   "Task_UART",   2048, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(TIME_PRINTER));
}

// FreeRTOS Idle Hook Callback
bool idle_hook_function() {
  // Microcontroller is idle in this state
  return true;
}

// Task 1: Reads acceleration from MPU6050 every 100 ms
void task_sensor(void *parameter) {
  sensors_event_t a, g, temp;

  for (;;) {
    mpu.getEvent(&a, &g, &temp);

    ax = a.acceleration.x;
    ay = a.acceleration.y;
    az = a.acceleration.z;

    vTaskDelay(pdMS_TO_TICKS(TIME_SAMPLE));
  }
  vTaskDelete(NULL);
}

// Task 2: Transmits data over UART and manages LED pulse
void task_uart(void *parameter) {
  for (;;) {
    printer();

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(TIME_BLINK));

    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(TIME_PRINTER - TIME_BLINK));
  }
  vTaskDelete(NULL);
}

// Function to format and output acceleration values over UART
void printer() {
  Serial.print("Accel X: ");
  Serial.print(ax);
  Serial.print(" Y: ");
  Serial.print(ay);
  Serial.print(" Z: ");
  Serial.println(az);
}