#include "cli.hpp"
#include "format/color.hpp"

int main(int argc, char** argv) {
  // set console mode on windows to be able to use ansi escape sequences
  veloq::format::enable_virtual_terminal();

  // parse args
  return veloq::handle_cli(argc, argv);
}