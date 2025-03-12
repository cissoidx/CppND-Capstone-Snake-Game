#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "obstacle.h"
#include "game.h"

// init static variable
int Obstacle::_idCnt = 0;
std::mutex Obstacle::_mtx;

void WaitingObstacles::pushBack(std::shared_ptr<Obstacle> obstacle, std::promise<void> &&promise) {
    std::lock_guard<std::mutex> lock(_mutex);

    _wobstacles.push_back(obstacle);
    _promises.push_back(std::move(promise));
}

void WaitingObstacles::permitEntryToFirstInQueue() {
    std::lock_guard<std::mutex> lock(_mutex);

    // get entries from the front of both queues
    auto firstPromise = _promises.begin();
    auto firstObstacle = _wobstacles.begin();

    // fulfill promise and send signal back that permission to enter has been granted
    firstPromise->set_value();

    // remove front elements from both queues
    _wobstacles.erase(firstObstacle);
    _promises.erase(firstPromise);
}

int WaitingObstacles::getSize() {
  return _wobstacles.size();
}

Obstacle::Obstacle()
  : _id(_idCnt++), 
    _x(-3),
    _y(-3) {
  for (size_t nx = 0; nx < 3; ++nx) {
    int obs_x = _x + nx;
    for (size_t ny = 0; ny < 3; ++ny) {
      int obs_y = _y + ny;
      SDL_Point body_cell{ static_cast<int>(obs_x), static_cast<int>(obs_y) };
      _body.push_back(body_cell);
    }
  }
}

void Obstacle::AttachToGame(std::shared_ptr<Game> game){
  _game = game;
}

void Obstacle::setPosition(int x, int y) {
  _x = x;
  _y = y;
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      _body.at(i*3+j).x = _x+i;
      _body.at(i*3+j).y = _y+j;
    }
  }
}

void Obstacle::run() {
  // print id of the current thread
  std::unique_lock<std::mutex> lck(_mtx);
  std::cout << "Obstacle #" << _id << "::run: thread id = " << std::this_thread::get_id() << std::endl;
  lck.unlock();
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (this->inGame()) {
      long timeSinceLastReborn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _last_reborn).count();
      if (timeSinceLastReborn >= _life) { this->setPosition(-3, -3); }
    }
    else {
      auto ftr = std::async(&Game::AddObstacleToQueue, _game, get_shared_this());
      ftr.get();
      _game->PlaceObstacle(get_shared_this());
      _last_reborn = std::chrono::system_clock::now();
    }
  }
}

bool Obstacle::inGame() {
  if (_x < 0) return false;
  return true;
}

