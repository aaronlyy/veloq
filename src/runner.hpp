#pragma once
#include "result.hpp"
#include <string>
#include <chrono>

namespace veloq {

  class Runner {
    public:
      explicit Runner(
        std::chrono::milliseconds timeout = std::chrono::milliseconds(10000), // time till veloq stops the execution
        bool verbose = false, // print command output live, could change runtime
        bool live = false // show live output
      );

      // run command once and save results
      Result run_once(const std::string &command);

      // run command many times and save results in a result collection
      ResultCollection run_multi(const std::string &command, const int &times);

    private:
      std::chrono::milliseconds timeout_;
      bool verbose_;
      bool live_;
  };

}