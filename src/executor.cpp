#include "executor.hpp"
#include "timer.hpp"
#include <string>
#include <iostream>
#include <chrono>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <stdio.h>
#endif

namespace veloq {
  Executor::Executor(const Config &config) : config_(config) {
    if (config_.verbose) {
      std::cout << "[veloq] Executor object was created\n";
    }
  }

  ExecutionData Executor::execute_command(const std::string &command) {
    if (config_.verbose) {
      std::cout << "[veloq] Executing command " << command << "\n";
    }

    Timer timer;
    ExecutionData execution_data;
    execution_data.command = command;
    timer.start();

    #ifdef _WIN32
    // windows execution
    #else
    // linux/unix execution
    #endif

    timer.stop();
    execution_data.timings = timer.timings();
    return execution_data;
  }
}