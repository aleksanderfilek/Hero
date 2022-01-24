#pragma once

#include<string>
#include<vector>
#include<unordered_map>

namespace Editor
{

enum class CmdType
{
  ERROR,
  QUIT,
  SHADER,
  MESH,
  SPRITESHEET
};

struct Cmd
{
  CmdType type;
  std::vector<std::string> args;
};

class Interpreter
{
private:
  static Interpreter* instance;

  std::unordered_map<std::string, CmdType> tokens;

public:
  Interpreter();
  ~Interpreter();

  static Cmd interpret(const std::string& command);
};

}