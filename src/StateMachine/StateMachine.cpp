#include "StateMacine.h"
#include "State.h"
#include "StateListener.h"

StateMachine::StateMachine() {
  // init state setup
  currentState = State::Init;
}

void StateMachine::transitionTo(State newState, const std::string& reason) {
  if(newState == currentState) return;

  State oldState = currentState;
  currentState = newState;

  notifyListeners(oldState, newState, reason);
  // somewhere here this sould be logged
}

void StateMachine::addListener(StateListener* listener) {
  listeners.push_back(listener);
}

void StateMachine::removeListener(StateListener* listener) {
  listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

void StateMachine::notifyListeners(State oldState, State newState, const std::string &msg) {
  StateTransitionEvent event{oldState, newState, msg};

  for(auto* listener : listeners) {
    listener->onStateChanged(event);
  }
}
