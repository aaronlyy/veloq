#pragma once

#include "config.hpp"
#include "timer.hpp"

#include <string>
#include <chrono>


// this class is used to execute commands, print command ouput, check for regex hits on output, trigger other commands
namespace veloq {

  enum class StreamType { Stdout, Stderr };
 
  struct ExecutionOutputLine {
    StreamType stream_type;
    std::string output_line;
    std::chrono::milliseconds offset;
    unsigned int line_number;
  };

  struct ExecutionOutput {
    std::vector<ExecutionOutputLine> execution_output_lines;
  };

  struct ExecutionData {
    std::string command;
    ExecutionOutput execution_output;
    Timings timings;
  };

  class Executor {
    public:
      explicit Executor(const Config &config);
      ExecutionData execute_command(const std::string &command);
    private:
      const Config &config_;
  };
}