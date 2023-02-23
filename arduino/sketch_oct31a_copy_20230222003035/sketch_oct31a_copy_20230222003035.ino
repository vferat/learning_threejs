#include <Wire.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

float ax, ay, az;      // Acceleration values
float vx = 0, vy = 0;  // Velocity values
float px = 0, py = 0;  // Position values
float gx, gy, gz;      // Rotation values

unsigned long t1, t2;  // Time variables

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  t1 = micros();
}

void loop() {
  t2 = micros();
  float dt = (t2 - t1) / 1000000.0;  // Time elapsed since last measurement
  t1 = t2;

  sensors_event_t accel_event, gyro_event, temp_event;
  mpu.getEvent(&accel_event, &gyro_event, &temp_event);

  ax = accel_event.acceleration.x;
  ay = accel_event.acceleration.y;
  az = accel_event.acceleration.z;
  gx = gyro_event.gyro.x;
  gy = gyro_event.gyro.y;
  gz = gyro_event.gyro.z;

  // Integrate acceleration to obtain velocity
  vx += ax * dt;
  vy += ay * dt;

  // Integrate velocity to obtain position
  px += vx * dt;
  py += vy * dt;

  // Send position and rotation data over serial port
  String gyro_str = String(gx) + "," + String(gy) + "," + String(gz);
  Serial.println(gyro_str);

}