#include"Interpreter.hpp"

#include<iostream>

namespace Editor
{

Interpreter* Interpreter::instance = nullptr;

inline static std::vector<std::string> split(const std::string& text, const std::string& delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  size_t startPos = 0;
  size_t endPos = 0;
  while((endPos = text.find(delimiter, startPos)) != std::string::npos)
  {
    token = text.substr(startPos, endPos - startPos);
    startPos = endPos+1;
    tokens.push_back(token);
  }

  token = text.substr(startPos, text.length() - startPos);
  tokens.push_back(token);

  return tokens;
}

Interpreter::Interpreter()
{
  instance = this;

  tokens["quit"] = CmdType::QUIT;
  tokens["shader"] = CmdType::SHADER;
  tokens["mesh"] = CmdType::MESH;
  tokens["spritesheet"] = CmdType::SPRITESHEET;
}

Interpreter::~Interpreter()
{

}

Cmd Interpreter::interpret(const std::string& command)
{
  Cmd cmd;

  std::vector<std::string> args = split(command, " \0\n");
  
  if(args.size() == 0 || instance->tokens.find(args[0]) == instance->tokens.end())
  {
    cmd.type = CmdType::ERROR;
    return cmd;
  }

  cmd.type = instance->tokens[args[0]];
  args.erase(args.begin(), args.begin() + 1);
  cmd.args = args;

  return cmd;
}

}