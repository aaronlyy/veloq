#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <vector>

namespace veloq {

  struct RunCollection;

  class Runner {
    public:
      explicit Runner(unsigned int runs_per_command = 5, bool live_output = false);

      RunCollection run(const std::string &command);

    private:
      unsigned int runs_per_command_;
      bool live_output_;
  };


  enum class StreamType { Stdout, Stderr };

  // saves single line of output and the corresponding time offset for later replay
  struct Output {
    StreamType stream;
    std::string output;
    std::chrono::milliseconds offset;
    int line = 0;
  };

  struct RunResult {
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
  // this struct only holds the raw run collection results
  // for analysis etc we going to use veloq::analysis::RunAnalyser
  struct RunCollection {
    std::string command;
    unsigned int runs_per_command;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    std::vector<RunResult> run_results;

    // time for all runs
    float runtime() const {
      if (run_results.empty()) {
        return 0.0f;
      }
      std::chrono::duration<float> diff = run_results.back().end_time - run_results[0].start_time;
      return diff.count();
    }

    // the average time of all runs
    float average_runtime() const {
        if (run_results.empty()){
          return 0.0f;
        }

        float total = 0.0f;
        for (const auto& run : run_results) {
            total += run.runtime();
        }

        return total / run_results.size();
    }

    // median runtime of all runs
    float median_runtime() const {
      if (run_results.empty()) {
        return 0.0f;
      }

      std::vector<float> runtimes;
      runtimes.reserve(run_results.size());

      for (const RunResult &run : run_results) {
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