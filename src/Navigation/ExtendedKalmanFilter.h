#pragma once

#include <cmath>
#include <vector>

class ExtendedKalmanFilter {
public:
  ExtendedKalmanFilter();

  void init(const std::vector<float> &initialState,
            const std::vector<std::vector<float>> &initialCovariance);
  void predict(const std::vector<float> &accelerometer,
               const std::vector<float> &gyroscope, float dt);
  void update(const std::vector<float> &measurment,
              const std::vector<std::vector<float>> &measurmentJacobian,
              const std::vector<std::vector<float>> &measurmentNoise);

  const std::vector<float> &getState() const { return state; }
  const std::vector<std::vector<float>> &getCovariance() const {
    return covariance;
  }

private:
  // State: [x, y, z, vx, vy, vz, roll, pitch, yaw, acc_bias_x, acc_bias_y,
  // acc_bias_z, gyro_bias_x, gyro_bias_y, gyro_bias_z]

  static constexpr int STATE_DIM = 15;
  std::vector<float> state;
  std::vector<std::vector<float>> covariance;

  // noise
  std::vector<std::vector<float>> processNoise;
  const float gravty = 9.81f;

  // helper
  std::vector<std::vector<float>> rotationMatrix(float roll, float pitch,
                                                 float yaw) const;
  std::vector<std::vector<float>>
  computeJacobian(const std::vector<float> &accel,
                  const std::vector<float> &gyro, float dt) const;
};
