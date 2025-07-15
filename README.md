# 🔍 SWV Debug Print Demo – STM32F303RE

This project demonstrates how to use **printf-style debugging** over **Serial Wire Viewer (SWV)** using **ITM** on the STM32F303RE Nucleo board.

Using SWV allows developers to debug real-time variables **without consuming UART pins**, taking advantage of ARM Cortex-M’s built-in instrumentation trace capabilities.

---

## 🎯 Objective

To configure STM32CubeIDE and STM32’s core debug peripherals to:
- Enable `printf()` via SWV and ITM
- Display variable values in real-time
- Monitor variables using **Live Expressions** for deeper insight
- Avoid UART usage for debug output

---

## 🛠 Project Requirements

- STM32F303RE Nucleo board  
- USB cable (ST-Link for power + debug)  
- STM32CubeIDE

---

## 🧪 Project Behavior

A counter variable is printed to the SWV ITM Console once per second:

```text
The counter value is: 0
The counter value is: 1
The counter value is: 2
...
```

Each line is printed using `printf()`, routed through `ITM_SendChar()` into the ARM debug subsystem.

---

## 🔧 How It Works

- `main()` initializes the HAL and enters an infinite loop
- A global counter is printed every 1 second using:
```c
printf("The counter value is: %d\r\n", count);
count++;
```
- The custom `_write()` syscall routes characters through `ITM_SendChar()`, sending data to **SWV Port 0**
- The output is visible in STM32CubeIDE’s **SWV ITM Data Console**

---

## 📄 License

This project is licensed under the STMicroelectronics software license (for HAL), and original contributions are under MIT License unless otherwise stated.
