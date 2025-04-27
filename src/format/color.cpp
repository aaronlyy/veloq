#ifdef _WIN32
  #include <windows.h>
#endif
#include "color.hpp"
#include <iostream>


namespace veloq::format {

  std::string to_escape(TextStyle text_style) {
    return std::string(ESCAPE) + std::to_string(static_cast<int>(text_style)) + M;
  }

  std::string format_rgb(uint8_t r, uint8_t g, uint8_t b, bool foreground) {
    return std::string(ESCAPE) + (foreground ? "38;2;" : "48;2;") +
           std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + M;
  }

  std::string reset() {
    return std::string(RESET_E);
  }

  std::string colorize(
    const std::string& text,
    std::optional<RGB> fg,
    std::optional<RGB> bg,
    const std::vector<TextStyle>& text_styles
  ) {
    std::string result;

    for (const TextStyle &text_style : text_styles) {
      result += to_escape(text_style);
    }

    if (fg) {
      auto [r, g, b] = *fg;
      result += format_rgb(r, g, b, true);
    }

    if (bg) {
      auto [r, g, b] = *bg;
      result += format_rgb(r, g, b, false);
    }

    result += text + reset();
    return result;
  }

  void print(
    const std::string& text,
    std::optional<RGB> fg,
    std::optional<RGB> bg,
    const std::vector<TextStyle>& text_styles
  ) {
    std::cout << colorize(text, fg, bg, text_styles) << std::endl;
  }

  // https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling
  void enable_virtual_terminal() {
    #ifdef _WIN32
      HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
      if (hOut == INVALID_HANDLE_VALUE) return;
  
      DWORD dwMode = 0;
      if (!GetConsoleMode(hOut, &dwMode)) return;
  
      dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      SetConsoleMode(hOut, dwMode);
    #endif
  }
}
