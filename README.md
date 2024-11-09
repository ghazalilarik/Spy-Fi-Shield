# Spy-Fi-Shield - Wi-Fi Intrusion Alert with Device Fingerprinting + Real-Time Attack Logger

![Meme](https://i.imgflip.com/5z7jjz.jpg)

*When your ESP8266 catches an unauthorized device trying to sneak into your network.*

## Overview
This ESP8266 project combines Wi-Fi intrusion detection with real-time attack logging. It monitors your Wi-Fi network for unauthorized devices and detects potential jamming (deauthentication attacks), providing alerts and logging suspicious activity.

---

## Disclaimer
This project is for educational and ethical use only. Unauthorized network monitoring may be restricted in some regions. Use responsibly and with permission. The authors are not responsible for any misuse or legal consequences.

---

## Features
- **Intrusion Detection**: Logs devices joining the network and identifies unauthorized devices based on MAC address filtering.
- **Deauthentication Attack Detection**: Monitors for deauthentication frames, which are commonly used in Wi-Fi jamming attacks.
- **LED Alerts**: Flashes an LED if unauthorized access or potential attacks are detected.
- **Web Dashboard**: Real-time logs of deauthentication packets and unauthorized devices.

## Installation

### Requirements
- **ESP8266** (e.g., NodeMCU)
- **Arduino IDE** with ESP8266 library
- **LED** (optional, for visual alert)
- **Wi-Fi credentials** (SSID and password)

### Setup
1. **Install ESP8266 Board in Arduino IDE**:
   - Go to **File > Preferences**.
   - Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` under **Additional Board Manager URLs**.
   - Go to **Tools > Board > Board Manager**, search for **ESP8266**, and install.

2. **Wiring**:
   - Connect an LED to GPIO pin **D4** with a resistor (220 ohms recommended).
   - Connect the LED anode (longer leg) to **D4** and the cathode to **GND**.

3. **Upload the Code**:
   - Replace `primarySSID`, `primaryPassword` with your network details.
   - Add MAC addresses of known devices in `knownDevices[]` to identify authorized devices.
   - Select the **ESP8266 board** and **COM port** in **Tools**, then upload the code.

4. **Access the Web Interface**:
   - Connect a device to the ESP8266’s network.
   - Enter the ESP8266’s IP address (usually `192.168.4.1`) in a browser to access the web dashboard.

---

## How to Use
1. **Intrusion Detection**:
   - The ESP8266 monitors connected devices.
   - Unauthorized devices trigger alerts and are logged on the web dashboard.
  
2. **Jammer Detection**:
   - Detects deauthentication frames used in jamming attacks.
   - An LED flashes as an alert when deauthentication packets reach a set threshold.

3. **Web Dashboard**:
   - View logs of detected deauthentication packets and unauthorized devices.
   - Use the dashboard to monitor network security in real time.

## Advantages
- Provides visibility into Wi-Fi security, alerting you to unauthorized devices and attacks.
- Easy to set up and monitor with the web dashboard.
- Lightweight, using minimal hardware for effective intrusion detection.

## Disadvantages
- Limited to detecting only deauthentication frames and unapproved MAC addresses.
- Unauthorized device alerts depend on accurate MAC address filtering.
- May not prevent attacks but provides monitoring and alerts.

## License
This project is open-source and available under the MIT License.
