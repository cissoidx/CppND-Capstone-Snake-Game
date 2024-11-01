#ifndef USERSCORE_H
#define USERSCORE_H

#include <string>

class UserScoreManager {
  public:
    UserScoreManager(std::string file_path);

    void UserScoreFromRecord(std::string query_user);
    void UpdateUserScoreRecord(std::string user, int score);

  private:
    std::string file_path_;
};

#endif