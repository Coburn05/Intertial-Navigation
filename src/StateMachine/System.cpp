#include "System.h"
#include "../Navigation/ExtendedKalmanFilter.h"
#include "State.h"
#include "StateMachine.h"
#include <memory>

System::System() {
  stateMachine.addListener(this);
  ekf = std::make_unique<ExtendedKalmanFilter>();
}

void System::onStateChanged(const StateTransitionEvent &event) {
  switch (event.to) {
  case State::Init:
    initializeComponents();
    break;

  case State::Calibrating:
    if (sensorManager.calibrateAll().status == CalibrationStatus::Success) {
      stateMachine.transitionTo(State::Running);
    } else {
      stateMachine.transitionTo(State::Error, "Calibration failure");
    }
    break;

  case State::Running:
    // start main controll
    break;

  case State::Error:
    // try recovery
    shutdownComponents();
    break;
  }
}

void System::run() { stateMachine.transitionTo(State::Init); }

void System::handleError(const std::string &error) {
  stateMachine.transitionTo(State::Error, error);
}

void System::initializeComponents() {
  sensorManager.autoDetectSensors();
  stateMachine.transitionTo(State::Calibrating);
}

void System::shutdownComponents() {
  sensorManager.stopPolling();
}
