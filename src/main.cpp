#include "cli.hpp"

int main(int argc, char** argv) {
  // just forward args to the cli, nothing else happens here
  return veloq::handle_cli(argc, argv);
}