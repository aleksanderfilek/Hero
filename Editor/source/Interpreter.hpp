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
  SPRITESHEET,
  TEXTURE,
  CUBEMAP
};

struct Cmd
{
  CmdType type;
  std::vector<std::string> args;
};

typedef void (*CmdFunc)(const Cmd& cmd);


class Interpreter
{
private:
  static Interpreter* instance;

  std::unordered_map<std::string, std::pair<CmdType, CmdFunc>> tokens;

public:
  Interpreter();
  ~Interpreter();

  static Cmd interpret(const std::string& command);
};

}