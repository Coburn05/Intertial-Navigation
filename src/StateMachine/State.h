#pragma once

#include <initializer_list>
#include <string>

enum class State { Init, Calibrating, Running, Error };

struct StateTransitionEvent {
  State from;
  State to;
  std::string msg;
};
