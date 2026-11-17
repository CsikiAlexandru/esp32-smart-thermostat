# ESP32 Smart Thermostat

Smart thermostat built on an ESP32 using C++ and PlatformIO. It reads temperature and humidity from a DHT11 sensor, shows live data on an OLED screen, switches an output (LED/relay) based on a target temperature, and hosts a local web page to control the threshold.

## How it works
- Reads temperature and humidity from a DHT11 every 2 seconds without blocking the web server.
- Displays the local IP address, current readings, target threshold, and relay/LED state on a 0.96" I2C OLED display.
- Serves an HTML interface stored in flash memory (`data/index.html` via LittleFS) where you can check status and update the temperature threshold from a phone or laptop.
- Structured into separate C++ classes (`Senzor`, `afisaj`, `termostat`) so new modules like a PIR motion sensor can be added easily later on.

## Hardware & Wiring

**Components:**
- ESP32 DevKit V1
- DHT11 temperature & humidity sensor
- 0.96" I2C OLED display (SSD1306, 128x64)
- LED (+ 220Ω resistor) or 5V relay module

**Connections:**

| Component | Pin | ESP32 Pin |
| :--- | :--- | :--- |
| DHT11 | Data | `GPIO 4` |
| OLED Display | SDA | `GPIO 21` |
| OLED Display | SCL | `GPIO 22` |
| LED / Relay | Signal | `GPIO 2` |
| All modules | VCC / GND | `3.3V` / `GND` |

## Setup & Upload
1. Open the project in VS Code with the PlatformIO extension installed.
2. Add your 2.4 GHz Wi-Fi credentials in `src/main.cpp`.
3. Upload the HTML file to flash: **PlatformIO -> Project Tasks -> Platform -> Upload Filesystem Image**.
4. Build and upload the firmware to the ESP32.
5. Read the IP address shown on the OLED display (or Serial Monitor at `115200` baud) and open it in your browser.

## Planned Improvements
- Live auto-updating web dashboard (JSON endpoint + `fetch`, no manual page refresh)
- Automated lighting using a PIR motion sensor