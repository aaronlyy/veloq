#include "timer.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include <chrono>

namespace veloq {

  #ifdef _WIN32
  // windows implementation

  long long Timer::frequency_ = 0;

  void Timer::initialize_frequency() {
    if (frequency_ == 0) {
      LARGE_INTEGER freq;
      QueryPerformanceFrequency(&freq);
      frequency_ = freq.QuadPart;
    }
  }

  void Timer::start() {
    timings_.start_time = std::chrono::system_clock::now();
    initialize_frequency();
    LARGE_INTEGER start;
    QueryPerformanceCounter(&start);
    start_ticks_ = start.QuadPart;
  }

  void Timer::stop() {
    LARGE_INTEGER stop;
    QueryPerformanceCounter(&stop);
    stop_ticks_ = stop.QuadPart;
    timings_.stop_time = std::chrono::system_clock::now();
    timings_.elapsed_seconds = static_cast<double>(stop_ticks_ - start_ticks_) / frequency_;
  }

  Timings Timer::timings() const {
    return timings_;
  }

  #else
  // linux & macos implementation

  void Timer::start() {
    timings_.start_time = std::chrono::system_clock::now();
    clock_gettime(CLOCK_MONOTONIC, &start_time_);
  }

  void Timer::stop() {
    clock_gettime(CLOCK_MONOTONIC, &stop_time_);
    timings_.stop_time = std::chrono::system_clock::now();
    double seconds = static_cast<double>(stop_time_.tv_sec - start_time_.tv_sec);
    double nanoseconds = static_cast<double>(stop_time_.tv_nsec - start_time_.tv_nsec) / 1e9;
    timings_.elapsed_time = seconds + nanoseconds;
  }

  Timings Timer::timings() const {
    return timings_;
  }
  #endif
}