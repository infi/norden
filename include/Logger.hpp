#pragma once

#if defined(DEBUG)
#include <iostream>
#endif
#include <string>

struct Logger {
  static void log(std::string message) {
#if defined(DEBUG)
    std::cout << message << std::endl;
#else
    (void)message;
#endif
  }
};