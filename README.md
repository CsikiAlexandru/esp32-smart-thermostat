# ESP32 Smart Thermostat

An IoT thermostat firmware built for ESP32 using C++ (OOP) and PlatformIO. Features digital temperature telemetry via DHT11, automated threshold control, and an embedded HTTP web server for remote setpoint management.

## Features
- **Digital Telemetry:** Real-time temperature sampling using DHT11.
- **Embedded Web UI:** Serves dynamic HTML control dashboard via `<WebServer.h>`.
- **OOP Architecture:** Decoupled hardware abstraction (`senzor`) and actuator logic (`termostat`).
- **RAII Safety:** Automatic GPIO pin teardown (safe OFF) on object destruction.

## Hardware Pinout
| Component | ESP32 GPIO | Mode | Description |
| :--- | :--- | :--- | :--- |
| **DHT11 Data** | `GPIO 4` | `INPUT` | Digital Data Signal |
| **Actuator / LED** | `GPIO 2` | `OUTPUT` | Active-HIGH Relay Control |

## Project Structure
```text
├── include/
│   ├── senzor.h
│   └── termostat.h
├── src/
│   ├── main.cpp
│   ├── senzor.cpp
│   └── termostat.cpp
├── platformio.ini
└── README.md