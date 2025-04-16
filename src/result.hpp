#pragma once

#include "output.hpp"

#include <string>
#include <vector>
#include <chrono>

namespace veloq {

  struct Result {
    std::string command;
    
    std::vector<Output> stdout_lines;
    std::vector<Output> stderr_lines;

    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;

    float runtime;

    bool timeout = false;
    int exit_code = 0;
  };

  struct ResultCollection {
    std::string command;
    unsigned int times;
    std::vector<Result> results;
    float average_runtime = 0.0f;
    float median_runtime = 0.0f;
  };

  void print_result(Result &result, bool show_output = false);
  void print_result(ResultCollection &result_collection, bool show_output = false);
}