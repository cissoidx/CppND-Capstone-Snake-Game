#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <chrono>
#include <mutex>
#include <future>


#include "snake.h"

class Game;

class Obstacle : public std::enable_shared_from_this<Obstacle> {
  public:
    enum class Direction { kUp, kDown, kLeft, kRight };

    Obstacle();

    int getID() { return _id; }
    std::vector<SDL_Point> getBody() {return _body; }
    void setPosition(int x, int y);
    std::vector<int> getPosition() {return {_x, _y}; };
    bool overlapSnake(Snake snake);
    void AttachToGame(std::shared_ptr<Game> game);
    void run();
    bool inGame();
    std::shared_ptr<Obstacle> get_shared_this() { return shared_from_this(); }

  private:
    std::shared_ptr<Game>  _game; // game that this obstacle is attached to
    int _id; // id of current instance
    // position is the uppper left point, no matter what the shape is. it can be outside the geometric figure
    int _x;  // x position of obstacle
    int _y;  // y position of obstacle
    float _speed; // moving speed of obstacle
    const double _life = 30000; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> _last_reborn;
    void UpdateBody(); 
    
    std::vector<SDL_Point> _body; // body of obstable
    static int _idCnt;
    static std::mutex _mtx; 
};

class WaitingObstacles {
  public:
    void pushBack(std::shared_ptr<Obstacle> obstacle, std::promise<void> &&promise);
    void permitEntryToFirstInQueue();
    int getSize();

  private:
    std::vector<std::shared_ptr<Obstacle>> _wobstacles;
    std::vector<std::promise<void>> _promises;
    std::mutex _mutex;
};

#endif