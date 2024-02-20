#include "cli_handler.hpp"
#include "file_handler.hpp"
#include "matrix.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "CLI mode" << std::endl;
    run_cli();
  } else if (argc == 2) {
    std::cout << "File mode" << std::endl;
    try {
      run_file(argv[1]);
    } catch (std::exception ex) {
      std::cout << "Error ocurred while working with file" << std::endl;
      std::cout << ex.what() << std::endl;
    }
  } else {
    std::cout << "Too many arguments provided" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
