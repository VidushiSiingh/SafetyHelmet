#define BLYNK_TEMPLATE_ID "TMPL3kV1tUsqr"
#define BLYNK_TEMPLATE_NAME "Fall Detection"
#define BLYNK_AUTH_TOKEN "7TM2p4sLYdO-VgMlDtPefso_Ud4Psj4e"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const char ssid[] = "Galaxy M311F11";      // Your Wi-Fi network name
const char password[] = "uorr8821";  // Your Wi-Fi password

Adafruit_MPU6050 mpu;
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

void sendSensor() {
  if (mpu.getMotionInterruptStatus()) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("AccelX:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(a.acceleration.z);
    Serial.print(", ");
    Serial.print("GyroX:");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print("GyroY:");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.print("GyroZ:");
    Serial.print(g.gyro.z);
    Serial.println("");
    
    Blynk.virtualWrite(V0, a.acceleration.x);
    Blynk.virtualWrite(V1, a.acceleration.y);
    Blynk.virtualWrite(V2, a.acceleration.z);
    Blynk.virtualWrite(V3, g.gyro.x);
    Blynk.virtualWrite(V4, g.gyro.y);
    Blynk.virtualWrite(V5, g.gyro.z);
    delay(200);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Blynk.begin(auth, ssid, password);
  timer.setInterval(100L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
