#pragma once

#include "State.h"
#include <memory>
#include <vector>

class StateListener;

class StateMachine {
public:
  StateMachine();

  void transitionTo(State newState, const std::string &reason = "default");
  State getCurrentState() const { return currentState; }

  void addListener(StateListener *listener);
  void removeListener(StateListener *listener);

private:
  State currentState = State::Init;
  std::vector<StateListener *> listeners;
  void notifyListeners(State oldState, State newState, const std::string &msg);
};
