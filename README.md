# 🎉 Birthday Countdown Project (ESP32 + SH1106 OLED)

## 📌 Overview
This is a fun embedded systems project built using ESP32.  
It displays a countdown on an OLED screen, controls LEDs, and plays a "Happy Birthday" tune using a buzzer.

---

## 🧰 Components Used
- ESP32 Dev Board  
- OLED Display 1.3" SH1106 (I2C)  
- Buzzer  
- 5 LEDs  
- Push Button (Built-in BOOT button)

---

## 🔌 Connections
| Component | ESP32 Pin |
|----------|----------|
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| Buzzer   | GPIO 4  |
| LEDs     | 18, 19, 17, 16, 15 |
| Button   | GPIO 0 (BOOT) |

---

## 📚 Libraries Required
- Adafruit GFX  
- Adafruit SH110X  

Install using Arduino Library Manager.

---

## ⚙️ Features
- 🔘 Press BOOT button to start countdown  
- ⏳ 10 to 0 countdown displayed on OLED  
- 💡 LED chasing effect during countdown  
- 🔊 Buzzer beeps when countdown ends  
- 🎶 Plays "Happy Birthday" melody  
- 🎇 LED disco effects  
- 🖥️ Displays "HAPPY BIRTHDAY" message  

---

## ▶️ How to Run
1. Upload the code to ESP32 using Arduino IDE  
2. Connect all components properly  
3. Press BOOT button  
4. Enjoy the birthday animation 🎉  

---

## 📸 Output
OLED shows countdown and birthday message with LED effects and sound.

---

## 👩‍💻 Author
Malaika Tauqeer  
BS Electrical Engineering (Robotics & Embedded Systems)

---
