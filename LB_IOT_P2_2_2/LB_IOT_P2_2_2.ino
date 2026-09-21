// ------------------------------------------------------------
//  Author: Miguel A.Lorenzo
//  Date: 21/09/2026
//  Subject: IoT Communications Laboratory 
//  Master: MSc in Electronic Engineering
//  University: University of Zaragoza EINA/UNIZAR
// ------------------------------------------------------------

/*
 * Microcontroller: ESP32
 * OS: FreeRTOS
 * Description: Multitasking program executing two independent concurrent tasks.
 *   - Task 1 (Blink_LED): Toggles an onboard LED (GPIO 2) every 200 ms.
 *   - Task 2 (Envio_UART): Sends "Hola mundo" over UART (115200 baud) every 1000 ms.
 *
 * xTaskCreate parameters breakdown:
 *   1. pvTaskCode    (TareaBlinkLED) : Pointer to the function that implements the task.
 *   2. pcName        ("Blink_LED")   : Descriptive string name for debugging purposes.
 *   3. usStackDepth  (2048)          : Stack size reserved for the task in bytes.
 *   4. pvParameters  (NULL)          : Pointer to argument variables passed into the task.
 *   5. uxPriority    (1)             : Execution priority (higher numbers = higher priority).
 *   6. pxCreatedTask (NULL)          : Task handle reference for external control/deletion.
 */

#include <Arduino.h>

#define LED_PIN 23

void TareaBlinkLED(void *parameter);
void TareaUART(void *parameter);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000);

  pinMode(LED_PIN, OUTPUT);

  xTaskCreate(TareaBlinkLED, "Blink_LED", 2048, NULL, 1, NULL);
  xTaskCreate(TareaUART, "Envio_UART", 2048, NULL, 1, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void TareaBlinkLED(void *parameter) {
  for (;;) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(200));

    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  vTaskDelete(NULL);
}

void TareaUART(void *parameter) {
  for (;;) {
    Serial.println("Hola mundo");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}