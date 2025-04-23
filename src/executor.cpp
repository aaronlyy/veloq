#include "executor.hpp"
#include <string>
#include <iostream>
#include <chrono>

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

    ExecutionData execution_data;
    execution_data.command = command;
    execution_data.start_time = std::chrono::system_clock::now();

    return execution_data;
  }
}