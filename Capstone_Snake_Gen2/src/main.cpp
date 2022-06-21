#include <iostream>
#include <unistd.h>
#include "controller.h"
#include "game.h"
#include "renderer.h"

void printHelp();

int main(int argc, char **argv)
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  __uint8_t mode, opt = 0;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  if (argc >= 2){
    if (strcmp(argv[1], "-s") == 0){
      mode = 0;
      std::cout<<"Single mode...\n";
      game.Run(controller, renderer, kMsPerFrame, mode);
    }
    else if (strcmp(argv[1], "-m") == 0){
      mode = 1;
      std::cout<<"Battle mode...\n";
      game.Run(controller, renderer, kMsPerFrame, mode);
    }
    else if (strcmp(argv[1], "-h") == 0){
      printHelp();
      return EXIT_FAILURE;
    }
    else{
      printHelp();
      return EXIT_FAILURE;
    }
  }
  else{
    game.Run(controller, renderer, kMsPerFrame, mode);
  }

  std::cout << "Game has terminated successfully!\n\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}

void printHelp()
{
  std::cout << "      >>> Welcome to the Snake Game 2.0 <<<"
            << "\n\n";
  std::cout << "Please select game mode by adding arguments: \n";
  std::cout << "1. -s: single mode.\n";
  std::cout << "2. -m: battle mode vs AI.\n\n";
}