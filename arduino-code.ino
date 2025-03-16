/* ------------------3 Idiots ----------------*/

#include <DHT.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// DHT Sensor setup
#define DHTPIN 2
#define DHTTYPE DHT11

// Ultrasonic setup
#define TRIGPIN 9
#define ECHOPIN 10
#define THRESHOLD 10

// Vibration thresholds
// Adjust these
#define LOW_VIB_THRESHOLD 0.2  
#define MED_VIB_THRESHOLD 0.4
#define HIGH_VIB_THRESHOLD 1.0

// Pin definitions for TFT LCD
#define TFT_CS     7
#define TFT_DC     6
#define TFT_RST    5
#define SDA_PIN    3  // SDA Pin
#define SCL_PIN    4  // SCL Pin

// Create the TFT display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Create DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

// Create MPU6050 sensor object
MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  // Setup DHT sensor
  dht.begin();
  
  // Setup ultrasonic sensor
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
  // Initialize MPU6050 sensor
  mpu.initialize();
  delay(2000);  // Wait for the sensor to initialize
  
  // Initialize TFT display
  tft.begin();
  tft.setRotation(3);  // Adjust rotation if necessary
  tft.fillScreen(ILI9341_RED);  // Set background to red
}

void loop() {
  // Read ultrasonic sensor
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  long duration = pulseIn(ECHOPIN, HIGH, 30000);
  float distance = duration * 0.034 / 2;

  if (duration == 0) {
    distance = -1;  // Invalid reading
  }

  // Read temperature from DHT sensor
  float temp = dht.readTemperature();
  
  if (!isnan(temp)) {
    Serial.print("TEMP: ");
    Serial.print(temp);
    Serial.print(" C, ");
  } else {
    Serial.println("FAILED TO READ FROM DHT SENSOR!");
    tft.setCursor(0, 10);
    tft.println("FAILED TO READ FROM DHT SENSOR!");
  }

  // Ultrasonic feedback
  if (distance > 0 && distance < THRESHOLD) {
    Serial.print("Distance: ");
    Serial.print(distance);
  }
  else{
    Serial.print("Distance is above threshold");
  }

  // Get vibration data from MPU6050
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Calculate acceleration magnitude
  float axG = ax / 16384.0;
  float ayG = ay / 16384.0;
  float azG = az / 16384.0;
  float accMagnitude = sqrt(axG * axG + ayG * ayG + (azG + 1.0) * (azG + 1.0));
  accMagnitude = abs(accMagnitude - 1.0);

  // Print vibration status
  if (accMagnitude < LOW_VIB_THRESHOLD) {
    Serial.println("LOW VIBRATION");
  } else if (accMagnitude < MED_VIB_THRESHOLD) {
    Serial.println("MEDIUM VIBRATION");
  } else if (accMagnitude < HIGH_VIB_THRESHOLD) {
    Serial.println("HIGH VIBRATION");
  }

  delay(1000);  // Delay to make the output readable
}
