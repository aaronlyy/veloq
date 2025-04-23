#pragma once

#include <string>
#include <chrono>
#include "config.hpp"

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
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    ExecutionOutput execution_output;
  };

  class Executor {
    public:
      explicit Executor(const Config &config);
      ExecutionData execute_command(const std::string &command);
    private:
      const Config &config_;
  };
}