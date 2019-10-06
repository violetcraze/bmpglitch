#include "./usage.h"

void usage::print()
{
  std::clog << "Usage:" << '\n'
            << '\n'
            << "\t" << logger::get_program_name() << " [options] <input_file>" << '\n'
            << '\n'
            << "Options:" << '\n'
            << "\t" << "-o <output_name>"
            << "\t\t" << "Specifies an output name."
            << '\n'
            << '\n';
}