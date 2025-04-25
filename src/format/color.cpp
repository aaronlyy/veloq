#include <iostream>
#include "format/color.hpp"

namespace veloq::format {
  std::string escape(const std::string &s) {
  return ESCAPE + s + M;
  }

  std::string format_rgb(unsigned short r, unsigned short g, unsigned short b) {
    return std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
  }

  std::string set_reset() {
    return RESET_E;
  }

  std::string set_fg_rgb(unsigned short r, unsigned short g, unsigned short b){
    return ESCAPE + FOREGROUND + format_rgb(r, g, b) + M;
  }

  std::string set_bg_rgb(unsigned short r, unsigned short g, unsigned short b){
    return ESCAPE + BACKGROUND + format_rgb(r, g, b) + M;
  }

  std::string set_bold() {
    return escape(BOLD);
  }

  std::string set_italic() {
    return escape(ITALIC);
  }

  std::string set_light() {
    return escape(LIGHT);
  }

  std::string set_underline() {
    return escape(UNDERLINE);
  }

  // print string with given rgb values as foreground
  void print_fg_rgb(const std::string &s, unsigned short r, unsigned short g, unsigned short b) {
    std::cout << set_fg_rgb(r, g, b) << s << RESET_E;
  }

  // print string with given rgb values as background
  void print_bg_rgb(const std::string &s, unsigned short r, unsigned short g, unsigned short b) {
    std::cout << set_bg_rgb(r, g, b) << s << RESET_E;
  }

  // print text with given foreground and background rgb values
  void print_rgb(const std::string &s, unsigned short fr, unsigned short fg, unsigned short fb, unsigned short br, unsigned bg, unsigned bb) {
    std::cout << set_bg_rgb(fr, fg, fb) << set_fg_rgb(br, bg, bb) << s << RESET_E;
  }

  void print_bold(const std::string &s) {
    std::cout << set_bold() << s << RESET_E;
  }

  void print_italic(const std::string &s) {
    std::cout << set_italic() << s << RESET_E;
  }

  void print_light(const std::string &s) {
    std::cout << set_light() << s << RESET_E;
  }

  void print_underline(const std::string &s) {
    std::cout << set_underline() << s << RESET_E;
  }
}