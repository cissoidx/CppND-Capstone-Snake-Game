#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"

class Game : public std::enable_shared_from_this<Game> {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void AddObstacleToQueue(std::shared_ptr<Obstacle> obs);
  void PlaceObstacle(std::shared_ptr<Obstacle> obs);
  void InitExtra();
  std::vector<std::shared_ptr<Obstacle>> GetObstacles(){ return _obstacles; }

  std::shared_ptr<Game> get_shared_this() { return shared_from_this(); }

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int grid_width;
  int grid_height;

  int score{0};

  void PlaceFood();
  void Update();

  int const _max_obs=3;
  int _obs_count=0;
  std::vector<std::thread> _threads;
  std::vector<std::shared_ptr<Obstacle>> _obstacles;
  WaitingObstacles _waiting_obstacles;
};

#endif