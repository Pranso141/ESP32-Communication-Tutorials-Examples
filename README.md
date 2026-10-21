# ESP32 Wireless Communication Protocols & Master Tutorials

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Framework](https://img.shields.io/badge/Framework-Arduino%20IDE-00979D.svg)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A comprehensive reference repository for ESP32 wireless communication protocols. This repository contains complete Arduino sketches (`.ino`), slide presentations (`.pdf`), step-by-step beginner guides, and web interfaces covering seven fundamental networking paradigms in IoT development.

---

## 📌 Protocol Comparison Matrix

| Protocol | Architecture | Network Topology | AP Required? | Payload Limit | Primary Use Case |
| :--- | :--- | :--- | :---: | :---: | :--- |
| **ESP-NOW** | Peer-to-Peer | 1:1, 1:N, N:1, N:N | ❌ No | 250 Bytes | Ultra-low latency, battery-powered sensor bursts |
| **ESP-MESH** | Tree / Multi-hop | Dynamic Self-Healing | ⚠️ Optional | Dynamic | Extended-range sensor networks across wide areas |
| **HTTP** | Client-Server | Point-to-Point | ✅ Yes | System Memory | REST API data ingestion, cloud logging |
| **MQTT** | Pub / Sub | Central Broker | ✅ Yes | System Memory | Telemetry, home automation, low-bandwidth IoT |
| **TCP** | Client-Server | Point-to-Point | ✅ Yes | Stream-based | Reliable byte streams, local PC-to-ESP control |
| **UDP** | Connectionless | Unicast / Broadcast | ✅ Yes | 65,507 Bytes | High-speed data streaming where packet loss is tolerable |
| **WebSockets** | Full-Duplex | Persistent Socket | ✅ Yes | System Memory | Real-time browser control dashboards & UI updates |

---

## 📂 Repository Architecture

```text
ESP32-Communication-Tutorials-Examples/
├── .gitignore
├── README.md
├── ESPMESH/
│   ├── ESP_MESH/
│   │   └── ESP_MESH.ino
│   ├── ESP_MESH PPT/
│   │   └── ESP MESH_Concepts.pdf
│   ├── ESP_MESH Tutorial/
│   │   └── ESP32 Mesh Tutorial.pdf
│   └── ESP_MESH Video/
│       └── ESPMESH.mp4
├── ESPNOW/
│   ├── ESP_NOW/
│   │   ├── ESP_NOW_Receiver/
│   │   │   └── ESP_NOW_Receiver.ino
│   │   └── ESP_NOW_Sender/
│   │       └── ESP_NOW_Sender.ino
│   ├── ESP_NOW PPT/
│   │   └── ESP-NOW_Concepts.pptx.pdf
│   ├── ESP_NOW Tutorial/
│   │   └── ESPNow Tutorial.pdf
│   └── ESP_NOW Video/
│       └── ESPNOW.mp4
├── HTTP/
│   ├── HTTP/
│   │   ├── HTTP_GET/
│   │   │   └── HTTP_GET.ino
│   │   └── HTTP_POST/
│   │       └── HTTP_POST.ino
│   ├── HTTP PPT/
│   │   └── HTTP_Concepts.pptx.pdf
│   ├── HTTP Tutorial/
│   │   └── HTTP Tutorial.pdf
│   └── HTTP Video/
│       └── HTTP.mp4
├── MQTT/
│   ├── MQTT/
│   │   └── MQTT.ino
│   ├── MQTT PPT/
│   │   └── MQTT_Concepts.pptx.pdf
│   ├── MQTT Tutorial/
│   │   └── MQTT Tutorial.pdf
│   └── MQTT Video/
│       └── MQTT.mp4
├── TCP/
│   ├── TCP/
│   │   └── TCP.ino
│   ├── TCP PPT/
│   │   └── TCP_Concepts.pptx.pdf
│   ├── TCP Tutorial/
│   │   └── TCP Tutorial.pdf
│   └── TCP Video/
│       └── TCP.mp4
├── UDP/
│   ├── UDP/
│   │   └── UDP.ino
│   ├── UDP PPT/
│   │   └── UDP_Concepts.pptx.pdf
│   ├── UDP Tutorial/
│   │   └── UDP Tutorial.pdf
│   └── UDP Video/
│       └── UDP.mp4
└── Websockets/
    ├── Websockets/
    │   ├── WebPage.txt
    │   └── Websockets.ino
    ├── Websockets PPT/
    │   └── ESP32_WebSocket_Concepts.pptx.pdf
    ├── Websockets Tutorial/
    │   └── WebSockets on ESP32 Guide (1).pdf
    └── Websockets Video/
        └── Websockets.mp4
```

---

## 💻 Hardware & Software Requirements

### Hardware Requirements

* **Microcontroller**: ESP32 Development Board (e.g., ESP32 Dev Module, NodeMCU-32S, DOIT ESP32 DEVKIT V1).
* **Connection**: USB Data Cable (ensure the cable supports data transfer lines, not power-only charging).
* **Network Environment**: 2.4 GHz Wi-Fi Router (ESP32 hardware does not support 5 GHz Wi-Fi bands).

### Software Requirements

* **IDE**: [Arduino IDE 2.x](https://www.arduino.cc/en/software)
* **PC Testing Tools**:
* [Packet Sender](https://packetsender.com/) (for raw TCP and UDP packet testing)
* Any standard modern Web Browser (for WebSockets client testing)



---

## ⚙️ Setup & Installation

### 1. Configure ESP32 Board Core in Arduino IDE

1. Open **Arduino IDE 2.x**.
2. Navigate to **File > Preferences**.
3. In **Additional Boards Manager URLs**, paste the following URL:
```text
[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)

```


4. Open **Tools > Board > Boards Manager...**, search for `esp32` by Espressif Systems, and click **Install**.
5. Select your board under **Tools > Board > esp32 > ESP32 Dev Module**.

### 2. Required External Libraries

Install the following libraries by opening **Tools > Manage Libraries...** (`Ctrl + Shift + I`):

| Protocol Module | Required Library | Author | Dependency Notes |
| --- | --- | --- | --- |
| **ESPMESH** | `painlessMesh` | guerra / spaniak | Auto-installs `ArduinoJson`, `TaskScheduler`, `AsyncTCP` |
| **MQTT** | `PubSubClient` | Nick O'Leary | None |
| **WebSockets** | `WebSockets` | Markus Sattler | None |

---

## 🚀 Protocol Guides & Quick Start

### 1. ESP-NOW (`/ESPNOW`)

Direct hardware-level frame communication over the 2.4 GHz Wi-Fi radio without joining an AP.

* **Key Concept**: Targeted unicast messaging using peer MAC addresses.
* **Quick Start**:
1. Upload `ESP_NOW_Receiver.ino` onto Board A and open the Serial Monitor (115200 baud) to view its MAC address.
2. Paste Board A's MAC address into `ESP_NOW_Sender.ino`.
3. Upload `ESP_NOW_Sender.ino` onto Board B to begin streaming data.



### 2. ESP-MESH (`/ESPMESH`)

Self-organizing, multi-hop tree mesh network built using `painlessMesh`.

* **Key Concept**: Automatically elects root and relay nodes without requiring a Wi-Fi router.
* **Quick Start**: Flash `ESP_MESH.ino` with identical `MESH_PREFIX` and `MESH_PASSWORD` definitions across two or more ESP32 boards.

### 3. HTTP Client (`/HTTP`)

Standard web client requests operating over the TCP/IP stack (`WiFi.h` and `HTTPClient.h`).

* **GET Example**: Fetches external JSON payloads from `http://ip-api.com/json`.
* **POST Example**: Sends structured JSON payloads to `http://jsonplaceholder.typicode.com/posts`.

### 4. MQTT Client (`/MQTT`)

Publish/Subscribe messaging designed for light-bandwidth IoT telemetry using `PubSubClient`.

* **Default Broker**: Configured out-of-the-box for `broker.hivemq.com` on Port 1883.
* **Topics**: Publishes telemetry on `esp32/trial/out` and subscribes to commands on `esp32/trial/in`.

### 5. TCP Server (`/TCP`)

Connection-oriented, reliable socket communication.

* **Default Configuration**: Runs a TCP Echo Server listening on local port `8080`.
* **Testing**: Connect via **Packet Sender** using TCP to the ESP32's assigned local IP address on port `8080`.

### 6. UDP Server (`/UDP`)

Connectionless datagram transmission for low-latency streaming.

* **Default Configuration**: Runs a UDP Echo Server listening on local port `4210`.
* **Testing**: Transmit UDP packets via **Packet Sender** to verify instant packet mirroring.

### 7. WebSockets (`/Websockets`)

Full-duplex persistent web socket connection between browser clients and the ESP32.

* **Server Port**: `81`
* **Interface Setup**: Open `WebPage.txt`, set the `ws://<ESP32_IP>:81/` address inside the script tag, save the file as `index.html`, and launch it in any web browser to control the onboard LED and view incoming telemetry.

---

## 🛠️ Testing & Debugging Tools

### Installing Packet Sender on Windows

To test raw TCP and UDP socket connections from a Windows machine, install Packet Sender via PowerShell or Command Prompt:

```cmd
winget install packetsender

```

### Serial Monitor Configuration

All sketches in this repository use a default baud rate of **`115200`**. Set the Arduino IDE Serial Monitor dropdown to **115200 baud** to view IP address assignments, debug output, and incoming payloads.

---

## 📜 License

This project is open-source software made available under the OpenGPL

```

```
