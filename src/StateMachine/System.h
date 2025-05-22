#pragma once

#include "../Sensors/SensorManager.h"
#include "State.h"
#include "StateListener.h"
#include "StateMachine.h"
#include <memory>

class ExtendedKalmanFilter;

class System : public StateListener {
public:
  System();

  // state  listener interface
  void onStateChanged(const StateTransitionEvent &event) override;

  void run();
  void handleError(const std::string &error);

private:
  StateMachine stateMachine;
  SensorManager sensorManager;
  std::unique_ptr<ExtendedKalmanFilter> ekf;

  void initializeComponents();
  void shutdownComponents();
};
