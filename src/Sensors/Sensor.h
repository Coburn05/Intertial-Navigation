#pragma once

#include <vector>
#include "SensorData.h"
#include "CalibrationStatus.h"

class Sensor {
public:
  virtual const std::vector<float>& read();
  virtual CalibrationResult calibrate() = 0;
  virtual ~Sensor() = default;

  protected:
    // common calibration verifivation
    bool validateCalibrationData(const std::vector<float>& data) {
      return !data.empty();
    }

    // common error builder
    CalibrationResult makeErrorResult(CalibrationStatus status, const std::string& msg) {
      return {status, msg, getCurrentTimestamp()};
    }
  
private:
  static double getCurrentTimestamp() {
    return 0;
  }

  SensorData data;
  int pollingPeriod; // time between polls in ms
  std::vector<float> noiseModel;
  
  void applyNoise(std::vector<float>& data) {
    for(size_t i = 0; i < data.size(); ++i) {
      data[i] += noiseModel[i];
    }
  }
  
};
