#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "userscore.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  const std::string kUserScorePath{"./user_score.txt"};

  std::string cuser = "";
  int cscore = 0;
  std::cout << "Please enter user: ";
  std::cin >> cuser;

  UserScoreManager usmgr(kUserScorePath);
  usmgr.UserScoreFromRecord(cuser);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  std::shared_ptr<Game> game = std::make_shared<Game>(kGridWidth, kGridHeight);
  game->InitExtra();
  // Game game(kGridWidth, kGridHeight);
  game->Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game->GetScore() << "\n";
  std::cout << "Size: " << game->GetSize() << "\n";

  cscore = game->GetScore();
  usmgr.UpdateUserScoreRecord(cuser, cscore);

  return 0;
}