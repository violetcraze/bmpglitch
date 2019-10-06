#include "logger.h"

static std::string program_name;

std::string log_flag(int flag)
{
  switch (flag)
  {
    case logger::flag::debug:
      return "DEBUG";
    case logger::flag::info:
      return "INFO ";
    case logger::flag::warn:
      return "WARN ";
    case logger::flag::error:
      return "ERROR";
  }
  return "?????";
}

std::string log_color(int flag)
{
  switch (flag)
  {
    case logger::flag::debug:
      return "\033[35m";
    case logger::flag::info:
      return "\033[34m";
    case logger::flag::warn:
      return "\033[33m";
    case logger::flag::error:
      return "\033[31m";
  }
  return "";
}

void logger::log(int flag, const std::string& message)
{
  if (flag == flag::error)
  {
    std::cerr << program_name << log_color(flag) <<  " |" << log_flag(flag) << "| " << message << "\033[0m" << '\n';
  }
  else
  {
    std::clog << program_name << log_color(flag) <<  " |" << log_flag(flag) << "| " << message << "\033[0m" << '\n';
  }
}

void logger::set_program_name(const std::string& name)
{
  program_name = name;
}

const std::string& logger::get_program_name()
{
  return program_name;
}
