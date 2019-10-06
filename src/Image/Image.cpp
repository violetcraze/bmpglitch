#include "./Image.h"

uint32_t uint32_from_buffer(char* b, int index)
{
  uint32_t i;
  i = b[index + 3];
  i = (i << 8) | b[index + 2];
  i = (i << 8) | b[index + 1];
  i = (i << 8) | b[index];
  return i;
}

uint16_t uint16_from_buffer(char* b, int index)
{
  uint16_t i;
  i = b[index + 1];
  i = (i << 8) | b[index];
  return i;
}

Image::Color get_color(char* b, int index)
{
  Image::Color c;
  c.r = b[index + 1];
  c.g = b[index + 2];
  c.b = b[index + 3];
  return c;
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

  f_size = uint32_from_buffer(f_b, 2);
  f_off_bits = uint32_from_buffer(f_b, 10);
  LINFO("Input file is " + std::to_string(f_size) + " bytes.");
  LDBUG("off_bits = " + std::to_string(f_off_bits));

  // load into buffer based on size in bytes

  uint32_t buffer_size = f_size - 14;
  char* b = new char[buffer_size];
  input.read(b, buffer_size);
  int off = 0;

  // image header

  i_size = uint32_from_buffer(b, 0);
  LDBUG("i_size = " + std::to_string(i_size));
  if (i_size == 40)
  {
    LINFO("Windows V3 Image Header being used.");

    i_width = uint32_from_buffer(b, 4);
    i_height = uint32_from_buffer(b, 8);
    LDBUG("i_width = " + std::to_string(i_width));
    LDBUG("i_height = " + std::to_string(i_height));

    if (b[12] != 1 || b[13] != 0)
    {
      LEROR("Invalid Image Header!");
      exit(exit_code::invalid_bmp_file);
    }

    i_bit_count = uint16_from_buffer(b, 14);
    i_compression = uint32_from_buffer(b, 16);
    i_size_image = uint32_from_buffer(b, 20);
    i_x_pix_meter = uint32_from_buffer(b, 24);
    i_y_pix_meter = uint32_from_buffer(b, 28);
    i_color_used = uint32_from_buffer(b, 32);
    i_color_important = uint32_from_buffer(b, 36);

    LDBUG("i_bit_count = " + std::to_string(i_bit_count));
    LDBUG("i_compression = " + std::to_string(i_compression));
    LDBUG("i_size_image = " + std::to_string(i_size_image));
    LDBUG("i_x_pix_meter = " + std::to_string(i_x_pix_meter));
    LDBUG("i_y_pix_meter = " + std::to_string(i_y_pix_meter));
    LDBUG("i_color_used = " + std::to_string(i_color_used));
    LDBUG("i_color_important = " + std::to_string(i_color_important));
  }
  else
  {
    LEROR("Unsupported Image Header!");
    exit(exit_code::invalid_bmp_file);
  }

  off += i_size;

  // color table

  if (i_bit_count <= 8)
  {
    int color_table_size = 1 << i_bit_count;
    LDBUG("color_table_size = " + std::to_string(color_table_size));

    for (int i = 0; i < color_table_size; i++)
    {
      LDBUG("offset = " + std::to_string(off + (i * sizeof(uint32_t))));
      color_table.push_back(get_color(b, off + (i * sizeof(uint32_t))));
    }

    #ifdef LEVEL_DEBUG
    for (size_t i = 0; i < color_table.size(); i++)
    {
      std::clog << std::hex << +color_table[i].r << " " << +color_table[i].g << " " << +color_table[i].b<< '\n';
    }
    #endif

    off += color_table_size * sizeof(uint32_t);
  }
  else
  {
    LEROR("Unsupported bit count!");
    exit(exit_code::invalid_bmp_file);
  }
  

  delete[] b;

}