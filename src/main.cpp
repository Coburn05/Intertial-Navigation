#include "StateMachine/System.h"

int main() {
  System robot;

  robot.run();

  // error handle
  robot.handleError("error thrown by me");

  return 0;
}
