# SWV Debug Print Demo

This project demonstrates how to use **`printf()`-style debugging** over **Serial Wire Viewer (SWV)** using **ITM** on the STM32F303RE Nucleo board. Unlike UART-based debugging, SWV lets developers **view debug output without using I/O pins** — thanks to the ARM Cortex-M’s built-in trace instrumentation. This is ideal for boards where UARTs are already occupied or unavailable.

---

## Problem

How can developers stream debug output from an STM32 without wiring up UART, consuming pins, or interfering with application resources?

---

## Method

- **Global Counter:** Incremented every second inside `main()`.  
- **Delay + Print:** Use `HAL_Delay(1000)` and `printf()` to output the value.  
- **Syscall Retargeting:** Redirect `_write()` → `ITM_SendChar()` to stream text via SWO Port 0.  
- **IDE Console:** View results inside STM32CubeIDE’s **SWV ITM Console**.  

Key code excerpt:  
```c
HAL_Delay(1000);  
printf("The counter value is: %d\r\n", count);  
count++;
```

---

## Result

The console output shows:  
The counter value is: 0  
The counter value is: 1  
The counter value is: 2  
The counter value is: 3  
...  

You can also add `count` to **Live Expressions** to monitor its value update in real time without halting execution.

---

## Hardware

- **STM32F303RE** Nucleo board  
- **ST-Link** (power, programming, SWV debug)  
- **STM32CubeIDE**

---

## SWV Setup (CubeIDE)

1. Start a Debug session.  
2. Open **SWV ITM Console**.  
3. Enable **Stimulus Port 0**.  
4. Click **Start Trace** to stream `printf()` messages live.  
5. Use **Live Expressions** to watch `count` increment continuously.  

---

## Takeaways

- SWV provides **lightweight, pin-free debugging**.  
- No UART setup or wiring required.  
- Minimal performance impact compared to blocking UART prints.  
- Ideal for monitoring system behavior in **resource-constrained or production environments**.  

| Feature                      | UART `printf()` | SWV via ITM |
|------------------------------|-----------------|-------------|
| Uses physical I/O pins       | ✅ Yes           | ❌ No        |
| Requires HAL UART setup      | ✅ Yes           | ❌ No        |
| Output visible in IDE        | ✅ Yes (COM port) | ✅ Yes (SWV console) |
| Affects timing/performance   | ⚠️ Yes (blocking) | ✅ Minimal   |
| Can run alongside UART apps  | ❌ Conflicts     | ✅ Compatible |

---
