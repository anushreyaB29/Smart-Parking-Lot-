# 🚗 Smart Parking System using Arduino

An Arduino-based Smart Parking System that automates vehicle entry and exit while managing parking occupancy for **three parking slots**. The system uses ultrasonic sensors to detect incoming and outgoing vehicles and controls a servo-operated barrier gate based on parking availability.

---

## 📌 Features

- 🚘 Detects vehicles approaching the entrance
- 🚪 Automatically opens the barrier gate if parking space is available
- 🚗 Detects vehicles leaving the parking area
- 📊 Maintains real-time occupancy count
- 🅿️ Supports a parking lot with **3 slots**
- 🔒 Prevents entry when all slots are occupied

---

## 🛠 Hardware Components

| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| HC-SR04 Ultrasonic Sensor | 2 |
| SG90 Servo Motor | 1 |
| Breadboard | 1 |
| Jumper Wires | Several |
| USB Cable / 5V Supply | 1 |

---

## ⚙️ Working Principle

### Vehicle Entry
An ultrasonic sensor placed near the entrance detects an approaching vehicle.

- If occupied slots < 3
  - Gate opens
  - Vehicle enters
  - Occupancy count increases
  - Gate closes automatically

- If occupied slots = 3
  - Gate remains closed
  - No additional vehicle is allowed

---

### Vehicle Exit
A second ultrasonic sensor placed near the exit detects vehicles leaving.

When a vehicle passes:
- Occupancy count decreases
- A parking slot becomes available

---

## 🔌 Pin Connections

| Device | Arduino Pin |
|--------|-------------|
| Entry Ultrasonic TRIG | D9 |
| Entry Ultrasonic ECHO | D10 |
| Exit Ultrasonic TRIG | D7 |
| Exit Ultrasonic ECHO | D8 |
| Servo Signal | D6 |
| VCC | 5V |
| GND | GND |

---

## 🅿️ Parking Capacity

Total Parking Slots : **3**

Occupancy is maintained internally by the Arduino program.

Example:

| Cars Parked | Available Slots |
|------------|----------------|
| 0 | 3 |
| 1 | 2 |
| 2 | 1 |
| 3 | 0 |

---

## 🚀 System Flow

```text
Vehicle Approaches Entrance
            │
            ▼
Entry Sensor Detects Vehicle
            │
            ▼
Occupied Slots < 3 ?
      ┌─────┴─────┐
      │           │
     Yes          No
      │           │
      ▼           ▼
Open Gate    Keep Gate Closed
      │
      ▼
Vehicle Enters
      │
      ▼
Occupied Count++
      │
      ▼
Close Gate


Vehicle Approaches Exit
            │
            ▼
Exit Sensor Detects Vehicle
            │
            ▼
Occupied Count--
            │
            ▼
Parking Space Available
```

---

## 🎯 Applications

- Shopping Malls
- Residential Complexes
- Office Buildings
- Colleges and Universities
- Smart City Parking Systems

---

## 🔮 Future Enhancements

- LCD display for available spaces
- RFID authentication
- ESP32 Wi-Fi monitoring
- Mobile application integration
- Multiple entry and exit lanes

---

## 👨‍💻 Authors

Developed as an Arduino-based embedded systems project demonstrating:

- Sensor Interfacing
- Servo Motor Control
- Occupancy Management
- Automation Techniques
- Smart Parking Concepts

⭐ If you found this project useful, consider giving it a star!