#include "controller.hpp"
#include "config.hpp"
#include "executor.hpp"

#include <iostream>

namespace veloq {
  Controller::Controller(const Config &config) : config_(config) {
    if (config_.verbose) {
      std::cout << "[veloq] Controller object created\n";
      std::cout << "[veloq] Loaded config\n";
      // add print config function
    }
  }

  void Controller::run() {
    if (config_.verbose) {
      std::cout << "[veloq] Controller.run() was called\n";
    }

    Executor executor(config_);
    executor.execute_command("dir");

    // setup regex stuff

    // setup runner with regex stuff and trigger stuff in config

    // pass runner into benchmark

    // print results
  }
}