#pragma once

#include <vector>

class SensorData {
public:
  const std::vector<float> getData();
  void setData(const std::vector<float> &newData);

protected:
  std::vector<float> data;
};
