#include "main.h"

int main(int argc, char** argv)
{
  logger::set_program_name(argv[0]);
  LINFO("Starting");
  arguments::Data args = arguments::parse(argc, argv);

  Bitmap i(args.input_file);

  glitch::lineending::apply(i);

  if (args.o_flag)
  {
    LINFO("Saving to \"" + args.o_string + "\".");
    i.save(args.o_string);
  }
  else
  {
    i.save("glitch.bmp");
  }

  LINFO("Ending");
  return exit_code::success;
}