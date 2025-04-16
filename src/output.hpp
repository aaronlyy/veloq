#pragma once
#include <vector>
#include <string>
#include <chrono>

namespace veloq {

  enum class StreamType { Stdout, Stderr };

  // saves single line of output and the corresponding time offset for later replay
  struct Output {
    StreamType stream;
    std::string output;
    std::chrono::milliseconds offset;
    int line = 0;
  };
}