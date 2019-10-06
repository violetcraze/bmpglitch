#include "arguments.h"

arguments::Data::Data()
{
  o_flag = false;
}

arguments::Data arguments::parse(int argc, char** argv)
{
  Data d;
  int option;
  while((option = getopt(argc, argv, "o:")) != -1)
  {
    switch (option)
    {
      case 'o':
        d.o_flag = true;
        break;
      case '?':
        usage::print();
        LEROR("Invalid Option!");
        exit(exit_code::invalid_option);
    }
  }
  return d;
}