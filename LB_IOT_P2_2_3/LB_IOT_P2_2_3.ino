// ------------------------------------------------------------
//  Author: Miguel A.Lorenzo
//  Date: 21/09/2026
//  Subject: IoT Communications Laboratory
//  Master: MSc in Electronic Engineering
//  University: University of Zaragoza EINA/UNIZAR
// ------------------------------------------------------------
/*
 * Microcontroller: ESP32 / Arduino Framework
 * OS: Non-OS (Polling / Millis-based scheduling)
 * Lab Assignment: Practical Exercise 2.3 (IoT Communications Laboratory)
 * Hardware: Adafruit MPU6050 (I2C Bus: SDA=GPIO21, SCL=GPIO22), Indicator LED (GPIO23)
 *
 * Description:
 *   Sequential implementation using non-blocking time checks (millis()).
 *   - Samples 3-axis acceleration every 100 ms via I2C bus.
 *   - Transmits acceleration values over UART every 1000 ms.
 *   - UART transmission raises a flag (flag_tx_event) to pulse the LED for 200 ms.
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define LED_PIN 23
#define TIME_SAMPLE 100
#define TIME_BLINK 200
#define TIME_PRINTER 1000

// Global variables to store acceleration values
float ax, ay, az;

// Time tracking variables for non-blocking execution
unsigned long time_sample = 0;
unsigned long cuurent_time_print_uart = 0;
unsigned long current_time_led = 0;

// Flags for event management and state control
bool flag_tx_event = false;
bool flag_led_active = false;

// Function declarations
void read_imu();
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
}

void loop() {

  // Read IMU sensor data every 100 ms
  if (millis() - time_sample >= TIME_SAMPLE) { 
    time_sample = millis();
    read_imu();
  }

  // Transmit acceleration metrics via UART every 1000 ms
  if (millis() - cuurent_time_print_uart >= TIME_PRINTER) {
    cuurent_time_print_uart = millis();
    flag_tx_event = true;  // Raise transmission flag to signal LED execution
    printer();
  }

  // Turn on LED upon receiving the transmission flag
  if (flag_tx_event) {
    digitalWrite(LED_PIN, HIGH);
    current_time_led = millis();
    flag_led_active = true;
    flag_tx_event = false; // Clear the trigger flag immediately
  }

  // Turn off LED after 200 ms elapsed
  if (flag_led_active && (millis() - current_time_led >= TIME_BLINK)) {
    digitalWrite(LED_PIN, LOW);
    flag_led_active = false;
  }
}

void read_imu() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
}

void printer() {
  Serial.print("Accel X: ");
  Serial.print(ax);
  Serial.print(" Y: ");
  Serial.print(ay);
  Serial.print(" Z: ");
  Serial.println(az);
}