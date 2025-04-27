#pragma once

#include <chrono>

namespace veloq {

  // this structs holds vague info about start and stop time of the executions
  // and a precise value of elapsed time
  struct Timings {
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point stop_time;
    double elapsed_seconds;

    double elapsed_milliseconds() const {
      return elapsed_seconds * 1000.0;
    }
    
    double elapsed_microseconds() const {
      return elapsed_seconds * 1'000'000.0;
    }
  };

  class Timer {
    public:
      void start();
      void stop();
      Timings timings() const;

    private:
      #ifdef _WIN32

      void initialize_frequency();
      static long long frequency_;
      long long start_ticks_ = 0;
      long long stop_ticks_ = 0;

      #else

      struct timespec start_time_{};
      struct timespec stop_time_{};

      #endif

      Timings timings_;
  };
}