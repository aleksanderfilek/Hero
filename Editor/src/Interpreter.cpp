#include"Interpreter.hpp"

namespace Editor
{

Interpreter* Interpreter::instance = nullptr;

inline static std::vector<std::string> split(const std::string& text, const std::string& delimiter)
{
  std::vector<std::string> tokens;
  std::string token;
  size_t pos = 0;
  while((pos = text.find(delimiter)) != std::string::npos)
  {
    token = text.substr(0, pos);
    tokens.push_back(token);
  }
  
  if(tokens.size() == 0)
  {
    tokens.push_back(text);
  }

  return tokens;
}

Interpreter::Interpreter()
{
  instance = this;

  tokens["quit"] = CmdType::QUIT;
}

Interpreter::~Interpreter()
{

}

Cmd Interpreter::interpret(const std::string& command)
{
  Cmd cmd;

  std::vector<std::string> args = split(command, " \0");
  if(args.size() == 0 || instance->tokens.find(command) == instance->tokens.end())
  {
    cmd.type = CmdType::ERROR;
    return cmd;
  }

  cmd.type = instance->tokens[args[0]];

  return cmd;
}

}