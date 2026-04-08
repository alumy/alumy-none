# alumy

A portable C utility library for embedded and bare-metal systems.

Alumy provides commonly needed building blocks — data structures, algorithms, drivers, protocols, and OS abstractions — so you can focus on your application logic instead of reinventing the wheel.

## Features

- **Crypto** — AES, SHA, HMAC, etc. (via mbedtls)
- **CRC / LRC** — CRC-8/16/32 and LRC
- **Data structures** — linked list, red-black tree, ring buffer (kfifo), bitmap, memory pool
- **Math & filters** — fixed-point math, PID controller, digital filters
- **String & encoding** — Base64, BCD, CSV parsing
- **Serialization** — cJSON, Protocol Buffers (protobuf-c)
- **File systems** — LittleFS, SPIFFS
- **Networking** — lwIP helpers, MQTT (Paho embedded), Modbus (FreeModbus)
- **Transfer protocols** — XMODEM / YMODEM / ZMODEM, LZMA compression
- **OSAL** — thin OS abstraction layer (FreeRTOS, bare-metal)
- **Drivers** — common peripheral driver interfaces
- **Shell** — interactive CLI (letter-shell)
- **Testing** — CUnit, Unity, CMock integration

## Requirements

- CMake >= 3.5
- C99-compatible toolchain (GCC / arm-none-eabi-gcc, etc.)

## Building

Use `cmake_gen.sh` to configure the project:

```bash
./cmake_gen.sh <toolchain> <build_type> <unit_test> <install_prefix>
```

Available toolchains (under `cmake/toolchain/`):

| Toolchain | Target |
|---|---|
| `gcc.cmake` | Native Linux (GCC) |
| `arm-none-eabi.cmake` | ARM Cortex-M (bare-metal) |
| `arm-fsl-linux-gnueabi.cmake` | ARM Linux (Freescale) |
| `stm32f103c8tx.cmake` | STM32F103C8Tx |
| `stm32f411ce.cmake` | STM32F411CE |
| `hc32f460petb.cmake` | HC32F460PETB |
| `hc32f460xe.cmake` | HC32F460xE |
| `xtensa-esp32.cmake` | ESP32 (Xtensa) |

Examples:

```bash
# Native Linux, Release build, install to /usr/local
./cmake_gen.sh gcc.cmake Release 0 /usr/local

# STM32F103, Debug build with unit tests
./cmake_gen.sh stm32f103c8tx.cmake Debug 1 /opt/alumy

# ARM bare-metal
./cmake_gen.sh arm-none-eabi.cmake Release 0 /opt/alumy
```

Then build and install:

```bash
cd build
make -j$(nproc)
sudo make install
```

## License

LGPL-2.1 — see [LICENSE](LICENSE) for details.
