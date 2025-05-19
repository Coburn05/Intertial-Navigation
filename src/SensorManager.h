#pragma once

#include "Sensor.h"
#include <vector>

class SensorManager {
public:
  int registerSensor(Sensor *sensor);
  void *getSensorData(Sensor *sensor);

private:
  std::vector<Sensor> sensorList;
};
