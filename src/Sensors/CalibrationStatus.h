#pragma once

enum class CalibrationStatus {
  Success = 0,
  Error,
  Timeount,
  InvalidData,
  NotSupported
};

struct CalibrationResult {
  CalibrationStatus status;
  std::string message;
  double timestamp; // when last calibration
};
