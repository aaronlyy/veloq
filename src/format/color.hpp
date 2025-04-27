#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <optional>
#include <cstdint>

namespace veloq::format {

  using RGB = std::tuple<uint8_t, uint8_t, uint8_t>;

  constexpr const char* ESCAPE = "\033[";
  constexpr const char* M = "m";
  constexpr const char* RESET_E = "\033[0m";

  enum class TextStyle {
    Reset = 0,
    Bold = 1,
    Light = 2,
    Italic = 3,
    Underline = 4,
    BlinkSlow = 5,
    BlinkRapid = 6,
    Invert = 7,
    Hide = 8,
    Crossed = 9
  };

  std::string to_escape(TextStyle text_style);
  std::string format_rgb(uint8_t r, uint8_t g, uint8_t b, bool foreground = true);
  std::string reset();

  std::string colorize(
    const std::string& text,
    std::optional<RGB> fg = {},
    std::optional<RGB> bg = {},
    const std::vector<TextStyle>& text_styles = {}
  );

  void print(
    const std::string& text,
    std::optional<RGB> fg = {},
    std::optional<RGB> bg = {},
    const std::vector<TextStyle>& text_styles = {}
  );

  void enable_virtual_terminal();
}
