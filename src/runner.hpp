#pragma once
#include "run.hpp"
#include <string>
#include <chrono>

namespace veloq {

  class Runner {
    public:
      explicit Runner(unsigned int runs_per_command = 5, bool live_output = false);

      RunCollection run(const std::string &command);

    private:
      unsigned int runs_per_command_;
      bool live_output_;
  };
}