#include "SensorManager.h"
#include "CalibrationStatus.h"
#include "Sensor.h"
#include <chrono>
#include <iostream>

SensorManager::SensorManager() = default;

SensorManager::~SensorManager() { stopPolling(); }

void SensorManager::registerSensor(std::unique_ptr<Sensor> sensor,
                                   const std::string &id) {
  std::lock_guard<std::mutex> lock(dataMutex_);
  sensors_[id] = {std::move(sensor), {}};
}

void SensorManager::deregisterSensor(const std::string &id) {
  std::lock_guard<std::mutex> lock(dataMutex_);
  sensors_.erase(id);
}

CalibrationResult SensorManager::calibrateAll() {
  std::lock_guard<std::mutex> lock(dataMutex_);

  for (auto &[id, entry] : sensors_) {
    auto result = entry.sensor->calibrate();
    if (result.status != CalibrationStatus::Success) {
      handleSensorError(id, "Calibration failed: " + result.message);
      return result;
    }
  }

  return {CalibrationStatus::Success, "All sensors calibrated", 0};
}

void SensorManager::startPolling(int baseRateHz) {
  pollingActive_ = true;
  pollingThread_ = std::thread(&SensorManager::pollingLoop, this, baseRateHz);
}

void SensorManager::stopPolling() {
  pollingActive_ = false;
  if (pollingThread_.joinable()) {
    pollingThread_.join();
  }
}

std::unordered_map<std::string, std::vector<float>>
SensorManager::getLatestData() {
  std::lock_guard<std::mutex> lock(dataMutex_);
  std::unordered_map<std::string, std::vector<float>> data;

  for (const auto &[id, entry] : sensors_) {
    data[id] = entry.latestData;
  }

  return data;
}

void SensorManager::pollingLoop(int baseRateHz) {
  const int intervalMs = 1000 / baseRateHz;

  while (pollingActive_) {
    auto start = std::chrono::steady_clock::now();

    {
      std::lock_guard<std::mutex> lock(dataMutex_);
      for (auto &[id, entry] : sensors_) {
        try {
          entry.latestData = entry.sensor->read();
        } catch (const std::exception &e) {
          handleSensorError(id, e.what());
        }
      }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    if (elapsed < intervalMs) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(intervalMs - elapsed));
    }
  }
}

void SensorManager::handleSensorError(const std::string &sensorId,
                                      const std::string &error) {
  std::cerr << "[SensorManager} Error in " << sensorId << ": " << error << "\n";

  // trigger state machine error handler??
  // if(stateMachine_) {...}
}
