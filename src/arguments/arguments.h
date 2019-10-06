#ifndef ARGUMENTS_H_INCLUDE
#define ARGUMENTS_H_INCLUDE

#include <string>
#include <unistd.h>
#include "../logger/logger.h"
#include "../usage/usage.h"
#include "../exitcode.h"

namespace arguments
{
  class Data
  {
    public:
      bool o_flag;
      
      std::string o_string;
      std::string input_file;

      Data();
      Data(const Data&) = default;
      ~Data() = default;
  };
  
  Data parse(int, char**);
} // namespace arguments


#endif /* ARGUMENTS_H_INCLUDE */