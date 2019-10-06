#include "main.h"

int main(int, char** argv)
{
  logger::set_program_name(argv[0]);
  LINFO("Starting");

  LINFO("Ending");
  return exit_code::success;
}