#include "utils.hpp"
#include <random>
#include <sstream>

namespace veloq {

  std::string generate_uuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::stringstream ss;
    for (int i = 0; i < 32; ++i) {
      ss << std::hex << dis(gen);
    }
    return ss.str();
  }
  
}