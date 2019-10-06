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
        d.o_string = optarg;
        d.o_flag = true;
        break;
      case '?':
        usage::print();
        LEROR("Invalid Option!");
        exit(exit_code::invalid_option);
    }
  }
  auto optindex = optind;
  LINFO("argc = " + std::to_string(argc));
  LINFO("optindex = " + std::to_string(optindex));
  if (optindex >= argc)
  {
    usage::print();
    LEROR("Not enough arguments!");
    exit(exit_code::not_enough_arguments);
  }
  d.input_file = argv[optindex];
  return d;
}