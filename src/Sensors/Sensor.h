#pragma once

#include <vector>
#include "SensorData.h"

class Sensor {
public:
  virtual const std::vector<float>& read();
  virtual int calibrate();  
  virtual ~Sensor() = default;
  
private:
  SensorData data;
  int pollingPeriod; // time between polls in ms
  std::vector<float> noiseModel;
  
  void applyNoise(std::vector<float>& data) {
    for(size_t i = 0; i < data.size(); ++i) {
      data[i] += noiseModel[i];
    }
  }
  
};
