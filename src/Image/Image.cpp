#include "./Image.h"

uint32_t uint_from_buffer(char* b, int index)
{
  uint32_t i;
  i = b[index + 3];
  i = (i << 8) | b[index + 2];
  i = (i << 8) | b[index + 1];
  i = (i << 8) | b[index];
  return i;
}

Image::Image(std::string bmp_path)
{
  std::ifstream input(bmp_path, std::ios::binary);
  if (sizeof(char) != 1)
  {
    LEROR("size of char is not 1 byte");
    exit(exit_code::other);
  }

  // file header

  char f_b[14]; // file header buffer
  input.read(f_b, 14);
  if (f_b[0] != 'B' || f_b[1] != 'M' || f_b[6] != 0 || f_b[7] != 0 || f_b[8] != 0 || f_b[9] != 0)
  {
    LEROR("Invalid bmp File Header!");
    exit(exit_code::invalid_bmp_file);
  }

  f_size = uint_from_buffer(f_b, 2);
  f_off_bits = uint_from_buffer(f_b, 10);
  LINFO("Input file is " + std::to_string(f_size) + " bytes.");
  LDBUG("off_bits = " + std::to_string(f_off_bits));

  // load into buffer based on size in bytes

  u_int32_t buffer_size = f_size - 14;
  char* b = new char[buffer_size];
  input.read(b, buffer_size);

  // image header

  

  delete[] b;

}