# Practica_2_LAB_Comunicaciones_IoT

# Practical Exercise 2: FreeRTOS Multitasking, I2C Sensor Sampling & Power Management

> **IoT Communications Laboratory**  
> MSc in Electronic Engineering — University of Zaragoza (EINA/UNIZAR)  
> **Author:** Miguel A. Lorenzo  
> **Date:** September 2026  

---

## 📌 Project Overview

This repository contains the full embedded C++ software implementation for **Practical Exercise 2** of the IoT Communications Laboratory. The main objective is to design, evaluate, and compare concurrent embedded software architectures on the **ESP32** microcontroller using both traditional polling logic and multi-threaded **FreeRTOS** Real-Time Operating System (RTOS) frameworks.

---

## 🛠️ Hardware Setup & Key Peripherals

* **Development Board:** ESP32 Development Board.
* **Inertial Sensor:** Adafruit MPU6050 connected over I2C bus (`SDA` = GPIO 21, `SCL` = GPIO 22).
* **Digital Outputs:** Status LED connected to `GPIO 23` (Transmission indicator pulse).
* **UART Interface:** Serial telemetry transmission at **115200 baud**.

---

## 🏗️ Exercises & System Architectures

1. **Exercise 2.2.2 — Basic FreeRTOS Multitasking:**  
   Creates two independent concurrent tasks running on FreeRTOS:
   * **Task 1:** Toggles an indicator LED (`GPIO 23`) every 200 ms.
   * **Task 2:** Transmits a `"HELLO WORLD"` string via UART every 1000 ms.

2. **Exercise 2.2.3 — I2C Sensor Sampling & UART Telemetry:**  
   Implements concurrent sensor reading and transmission using FreeRTOS tasks:
   * **Task 1 (Sensor):** Samples 3-axis acceleration metrics from the MPU6050 IMU every 100 ms via I2C.
   * **Task 2 (UART/LED):** Outputs telemetry data via Serial every 1000 ms and triggers a non-blocking 200 ms LED pulse upon transmission.

3. **Exercise 2.2.4 — FreeRTOS Low-Power Optimization (Idle Hook):**  
   Enhances Exercise 2.2.3 by integrating low-power management:
   * Configures an Idle Task Hook (`esp_register_freertos_idle_hook`) to place CPU cores into low-power mode whenever all active tasks are blocked in `vTaskDelay`.

---

## 📂 Project Structure

```text
.
├── LB_IOT_P2_2_2/
│   └── LB_IOT_P2_2_2.ino     # Exercise 2: Basic multitasking (LED Blink + UART)
├── LB_IOT_P2_2_3/
│   └── LB_IOT_P2_2_3.ino     # Exercise 3: MPU6050 sampling + UART telemetry & LED pulse
├── LB_IOT_P2_2_4/
│   └── LB_IOT_P2_2_4.ino     # Exercise 4: FreeRTOS Low-Power optimization (Idle Hook)
└── README.md                 # Repository documentation
```

---

## 📚 Reference Material & Documentation

* [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
* [Installing ESP32 Core in Arduino IDE](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* [Espressif Arduino-ESP32 Official Libraries API](https://github.com/espressif/arduino-esp32/tree/master/libraries)
* [FreeRTOS Official Book & Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
* [ESP32 FreeRTOS Reference Examples](https://github.com/uagaviria/ESP32_FreeRtos)
* [FreeRTOS Idle Task Hook Functions (`vApplicationIdleHook`)](https://freertos.org/a00016.html)
* [ESP32 FreeRTOS Task Management & Priorities](http://www.iotsharing.com/2017/06/arduino-esp32-freertos-how-to-use-task-param-task-priority-task-handle.html)

---

## 🚀 How to Build & Run

1. Open any of the exercise folders (`LB_IOT_P2_2_X`) in **Arduino IDE**.
2. Select **ESP32 Dev Module** under the `Tools > Board` menu.
3. Ensure the MPU6050 sensor is properly connected to I2C pins (`GPIO 21` / `GPIO 22`) and the LED to `GPIO 23`.
4. Upload the sketch and open the Serial Monitor at **115200 baud** to view real-time log outputs and sensor telemetry.
