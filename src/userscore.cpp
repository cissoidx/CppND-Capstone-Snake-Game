#include "userscore.h"
#include <vector>

UserScoreManager::UserScoreManager(std::string file_path)
    : file_path_(file_path) {}

void UserScoreManager::UserScoreFromRecord(std::string query_user){
  std::string line;
  std::ifstream filestream(file_path_);
  std::string user;
  int score;
  if (filestream.is_open()){
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> user >> score){
        if (user == query_user){
          std::cout << "User " << user << " has a record of " << score << ".\n";
          return void();
        }
      }
    }
  }
}

void UserScoreManager::UpdateUserScoreRecord(std::string cuser, int cscore){
  std::ifstream inFile(file_path_);
  std::vector<std::string> lines;
  bool exist = false;
  std::string line;
  auto new_line = cuser + " " + std::to_string(cscore);
  std::string user;
  int score;
  while (std::getline(inFile, line)){
    std::istringstream linestream(line);
    while (linestream >> user >> score){
      if (user == cuser){
        exist = true;
        if (score < cscore) lines.push_back(new_line);
      }
      else {
        lines.push_back(line);
      }
    }
  }
  if (!exist) lines.push_back(new_line);

  inFile.close();

  std::ofstream outFile(file_path_, std::ios::out);
  if (!outFile.is_open()) {
        std::cerr << "Cannot write to file " << file_path_ << std::endl;
        return void();
  }
  for (const auto& modifiedLine : lines) {
    outFile << modifiedLine << std::endl;
  }
  outFile.close(); 
}