#include "./Image.h"

Image::Image(std::string bmp_path)
{
  std::ifstream input(bmp_path, std::ios::binary);
  if (sizeof(char) != 1)
  {
    LEROR("size of char is not 1 byte");
    exit(exit_code::other);
  }
  char b[1000];
  input.read(b, 14);
  if (b[0] != 'B' || b[1] != 'M' || b[6] != 0 || b[7] != 0 || b[8] != 0 || b[9] != 0)
  {
    LEROR("Invalid bmp Header!");
    exit(exit_code::invalid_bmp_file);
  }
}