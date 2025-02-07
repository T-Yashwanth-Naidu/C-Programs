#include "sensors.h"

void ultrasonic_sensor_update(struct UltrasonicSensor *self, float distance) {
  if (!self)
    return;
  self->distance = distance;
}

void speed_sensor_update(struct SpeedSensor *self, float speed) {
  if (!self)
    return;
  self->speed = speed;
}

void brake_pressure_sensor_update(struct BrakePressureSensor *self,
                                  float pressure) {
  if (!self)
    return;
  self->pressure = pressure;
}
