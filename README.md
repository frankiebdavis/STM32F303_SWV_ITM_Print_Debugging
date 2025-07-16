# 🧠 SWV Debug Print Demo – STM32F303RE

This project demonstrates how to use **`printf()`-style debugging** over **Serial Wire Viewer (SWV)** using **ITM** on the STM32F303RE Nucleo board.

Unlike UART-based debugging, SWV lets developers **view debug output without using any I/O pins** — thanks to the ARM Cortex-M’s built-in trace instrumentation hardware. This makes it ideal for production boards where UARTs are already in use or unavailable.

---

## 🎯 Project Goal

To configure STM32CubeIDE and STM32’s debug infrastructure to:

- Enable `printf()` over SWV via ITM  
- Display variable values in real time  
- Use **Live Expressions** to inspect variables dynamically  
- Avoid consuming UART resources for debug output

---

## 🔧 Hardware Used

- **STM32F303RE** Nucleo Board  
- **ST-Link USB interface** (for programming + SWV debugging)  
- **STM32CubeIDE**

---

## 🚦 What This Project Does

A simple global counter is printed to the **SWV ITM Console** once per second using `printf()`:

```text
The counter value is: 0
The counter value is: 1
The counter value is: 2
...
```

This demonstrates how SWV can be used to stream debug data — with no interrupts, no UART config, and no pin routing required.

---

## 💻 How It Works

The `main()` loop includes a global variable `count` that increments every second:

```c
HAL_Delay(1000);
printf("The counter value is: %d\r\n", count);
count++;
```

The `printf()` output is routed via a custom `_write()` syscall implementation, which sends characters through `ITM_SendChar()` — the standard way to stream data to **SWV Port 0**.

### 🔍 Live Expressions

To further monitor variables in real time:

- Open the **Live Expressions** tab in STM32CubeIDE
- Add the `count` variable to watch
- Observe it update every second, even without halting the MCU

This is extremely useful for visualizing dynamic values during long-running processes or state changes.

---

## 🧠 Why Use SWV?

SWV debugging is lightweight, pin-free, and ideal for:

| Feature                      | UART `printf()` | SWV via ITM |
|------------------------------|-----------------|-------------|
| Uses physical I/O pins       | ✅ Yes           | ❌ No        |
| Requires HAL UART setup      | ✅ Yes           | ❌ No        |
| Output visible in IDE        | ✅ Yes (via COM port) | ✅ Yes (SWV console) |
| Affects timing/performance   | ⚠️ Yes (blocking) | ✅ Minimal   |
| Can run alongside UART apps  | ❌ Conflicts     | ✅ Compatible |

---

## 📘 License

This project is licensed under the [MIT License](LICENSE).  
