// ------------------------------------------------------------
//  Author: Miguel A.Lorenzo
//  Date: 21/09/2026
//  Subject: IoT Communications Laboratory 
//  Master: MSc in Electronic Engineering
//  University: University of Zaragoza EINA/UNIZAR
// ------------------------------------------------------------

/*
 * Microcontroller: ESP32 WROOM 
 * OS: FreeRTOS
 * Description: Multitasking program executing two independent concurrent tasks.
 *   - Task 1 (Blink_LED): Toggles an onboard LED (GPIO 2) every 200 ms.
 *   - Task 2 (Printer_UART): Sends "HELLO WORLD" over UART (115200 baud) every 1000 ms.
 *
 * xTaskCreate parameters breakdown:
 *   1. pvTaskCode    (task_blink_led) : Pointer to the function that implements the task.
 *   2. pcName        ("Blink_LED")   : Descriptive string name for debugging purposes.
 *   3. usStackDepth  (2048)          : Stack size reserved for the task in bytes.
 *   4. pvParameters  (NULL)          : Pointer to argument variables passed into the task.
 *   5. uxPriority    (1)             : Execution priority (higher numbers = higher priority).
 *   6. pxCreatedTask (NULL)          : Task handle reference for external control/deletion.
 */

#include <Arduino.h>

#define LED_PIN 23
#define TIME_BLINK 200
#define TIME_PRINTER 1000

//FUNCTIONS DECLARATION
void task_blink_led(void *parameter);
void task_printer_uart(void *parameter);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000);

  pinMode(LED_PIN, OUTPUT);

  xTaskCreate(task_blink_led, "Blink_LED", 2048, NULL, 1, NULL);
  xTaskCreate(task_printer_uart, "Printer_UART", 2048, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(TIME_PRINTER));
}

void task_blink_led(void *parameter) {
  for (;;) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(TIME_BLINK));

    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(TIME_BLINK));
  }
  vTaskDelete(NULL);
}

void task_printer_uart(void *parameter) {
  for (;;) {
    Serial.println("HELLO WORLD");
    vTaskDelay(pdMS_TO_TICKS(TIME_PRINTER));
  }
  vTaskDelete(NULL);
}