#include "main.h"

int main(int argc, char** argv)
{
  logger::set_program_name(argv[0]);
  LINFO("Starting");
  arguments::Data args = arguments::parse(argc, argv);

  Image i(args.input_file);

  i.save("test.bmp");

  LINFO("Ending");
  return exit_code::success;
}