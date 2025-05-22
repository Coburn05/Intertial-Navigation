#pragma once

#include "State.h"

class StateListener {
  public:
    virtual void onStateChanged(const StateTransitionEvent& event) = 0;
    virtual ~StateListener() = default;
};
