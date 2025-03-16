# **Mad Angry Mom Telemetry System**

This is a **real-time telemetry system** that tracks **acceleration, temperature, and distance** using an **MPU6050 accelerometer, DHT11 temperature sensor, and an ultrasonic sensor**. Instead of just displaying data, it **yells at you like an angry mom**, thanks to **Gemini AI** and **11Labs TTS**.

---
# **Assemble Instructions**

Parts you need: DHT11 (Temperature Sensor), Ultrasonic sensor, MPU6050, optionally an TFT-LCD display, Arduino UNO

DHT11 -> D2

TRIG -> D9

ECHO -> D10

MPU6050 (SDA) -> A4

MPU6050 (SCL) -> A5

## **How to Run the AI System**

### **Google Colab (Recommended)**
To recreate the AI scolding system, **Google Colab is the best choice** since it provides a **preconfigured Python environment** without needing manual installations.

1. Open **Google Colab**.
2. Upload the provided `.ipynb` file.
3. Run the cell to experience **AI-generated angry mom reactions**.

### **Local Setup**
If you prefer to run it locally, install the required dependencies:

```bash
pip install google
pip install pygame
pip install requests
