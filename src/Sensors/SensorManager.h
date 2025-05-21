#pragma once

#include "CalibrationStatus.h"
#include "Sensor.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

class SensorManager {
public:
  SensorManager();
  ~SensorManager();

  // sensor managment
  void registerSensor(std::unique_ptr<Sensor> sensor, const std::string &id);
  void deregisterSensor(const std::string &id);
  void autoDetectSensors();

  // calibration
  CalibrationResult calibrateAll();
  CalibrationResult calibrateSensor(const std::string &id);

  // data collection
  void startPolling(int basePollingRateHz = 100);
  // this logic might change? want to be able to poll diff sensor at diff speed

  void stopPolling();
  std::unordered_map<std::string, std::vector<float>> getLatestData();

  // will need to add something about state machine integration later

private:
  struct SensorEntry {
    std::unique_ptr<Sensor> sensor;
    int pollingPeriodMs;
    std::vector<float> latestData;
  };

  std::unordered_map<std::string, SensorEntry> sensors_;
  std::mutex dataMutex_;
  std::atomic<bool> pollingActive_{false};
  std::thread pollingThread_;
  // state machine should be stored as well

  void pollingLoop(int paseRateHz);
  void handleSensorError(const std::string &id, const std::string &error);
};
