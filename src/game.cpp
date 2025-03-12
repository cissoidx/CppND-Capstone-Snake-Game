#include "game.h"
#include <iostream>
#include <algorithm>
#include <thread>

#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      grid_width(grid_width),
      grid_height(grid_height) {
  PlaceFood();
}

Game::~Game() {
  std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
    t.join();
  });
}


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, _obstacles);
    

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::InitExtra() {
  for (size_t no = 0; no < _max_obs; no++) {
    _obstacles.push_back(std::make_shared<Obstacle>());
  }
  for (auto obs : _obstacles){
    _threads.emplace_back(std::thread(&Obstacle::run, obs));
    obs->AttachToGame(get_shared_this());
  }
  snake.AttachToGame(get_shared_this());
}


void Game::AddObstacleToQueue(std::shared_ptr<Obstacle> obs) {
  // add new obstacle to the end of the waiting queue
  std::promise<void> prmsObstacleAllowedToShow;
  std::future<void> ftrObstacleAllowedToShow = prmsObstacleAllowedToShow.get_future();
  _waiting_obstacles.pushBack(obs, std::move(prmsObstacleAllowedToShow));

  ftrObstacleAllowedToShow.wait();
}


void Game::PlaceObstacle(std::shared_ptr<Obstacle> obs) {
  int x, y;
  bool overlap = true;
  while (overlap) {
    // do not place at the edge
    x = (random_w(engine) + 1) % (grid_width - 1);
    y = (random_h(engine) + 1) % (grid_height - 1);

    // snake body does not overlap obstacle
    for (auto const &item : snake.body) {
      if (!((item.x < x ) || (item.x > x + 2) || (item.y < y ) || (item.y > y + 2))) {
        continue;
      }
    }

    // snake head does not overlap obstacle
    if (!(((int)snake.head_x < x ) || ((int)snake.head_x > x + 2) || 
    ((int)snake.head_y < y ) || ((int)snake.head_y > y + 2))) {
      continue;
    }

    // food does not overlap obstacle
    if (!((food.x < x ) || (food.x > x + 2) || (food.y < y ) || (food.y > y + 2))) {
      continue;
    }

    overlap = false;
  }
  obs->setPosition(x, y);
}


// void Game::SnakeHitObstacle() {

// }


void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    if (_waiting_obstacles.getSize() > 0) {
      _waiting_obstacles.permitEntryToFirstInQueue();
    }
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }