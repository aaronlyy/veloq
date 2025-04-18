#pragma once

#include "output.hpp"

#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

namespace veloq {

  // result of a single command run
  struct Run {
    std::string command;
    
    std::vector<Output> stdout_lines;
    std::vector<Output> stderr_lines;

    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;

    float runtime() const {
      std::chrono::duration<float> diff = end_time - start_time;
      return diff.count();
    }

    int exit_code = 0;
  };

  // result of multiple runs of the same command
  struct RunCollection {
    std::string command;
    unsigned int runs_per_command;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::vector<Run> runs;

    // time for all runs
    float runtime() const {
      if (runs.empty()) {
        return 0.0f;
      }
      std::chrono::duration<float> diff = runs.back().end_time - runs[0].start_time;
      return diff.count();
    }

    // the average time of all runs
    float average_runtime() const {
        if (runs.empty()){
          return 0.0f;
        }

        float total = 0.0f;
        for (const auto& run : runs) {
            total += run.runtime();
        }

        return total / runs.size();
    }

    // median runtime of all runs
    float median_runtime() const {
      if (runs.empty()) {
        return 0.0f;
      }

      std::vector<float> runtimes;
      runtimes.reserve(runs.size());

      for (const auto& run : runs) {
        runtimes.push_back(run.runtime());
      }

      std::sort(runtimes.begin(), runtimes.end());

      size_t n = runtimes.size();
      if (n % 2 == 1) {
        return runtimes[n / 2];
      } else {
        return (runtimes[n / 2 - 1] + runtimes[n / 2]) / 2.0f; 
      }
    }
  };
}