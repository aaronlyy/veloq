#pragma once

#include "config.hpp"

// controller uses config and first checks what main

namespace veloq {

  class Controller {
    public:
      explicit Controller(const Config &config);
      void run();
    private:
      const Config &config_;
  };
}