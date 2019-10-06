#include "main.h"

int main(int argc, char** argv)
{
  logger::set_program_name(argv[0]);
  LINFO("Starting");
  arguments::parse(argc, argv);
  
  LINFO("Ending");
  return exit_code::success;
}