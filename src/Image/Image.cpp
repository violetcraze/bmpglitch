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

void uint32_to_out(std::ofstream& o, u_int32_t i)
{
  o.put(i & 0xFF);
  o.put((i >> 8) & 0xFF);
  o.put((i >> 16) & 0xFF);
  o.put((i >> 24) & 0xFF);
}

uint16_t uint16_from_buffer(char* b, int index)
{
  uint16_t i;
  i = b[index + 1];
  i = (i << 8) | b[index];
  return i;
}

void uint16_to_out(std::ofstream& o, u_int16_t i)
{
  o.put(i & 0xFF);
  o.put((i >> 8) & 0xFF);
}

Image::Color get_color(char* b, int index)
{
  Image::Color c;
  c.r = b[index + 2];
  c.g = b[index + 1];
  c.b = b[index];
  return c;
}

void color_to_out(std::ofstream& o, Image::Color& c)
{
  o.put(c.b);
  o.put(c.g);
  o.put(c.r);
  o.put(0);
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
    color_table_size = 1 << i_bit_count;
    LDBUG("color_table_size = " + std::to_string(color_table_size));

    color_table = new Image::Color[color_table_size];

    for (size_t i = 0; i < color_table_size; i++)
    {
      color_table[i] = get_color(b, off + (i * sizeof(uint32_t)));
    }

    off += color_table_size * sizeof(uint32_t);
  }
  else
  {
    LEROR("Unsupported bit count!");
    exit(exit_code::invalid_bmp_file);
  }
  
  // Pixel Data

  if (i_bit_count == 4)
  {
    pixel_data_size = i_width * i_height;
    pixel_data = new char[pixel_data_size];
    for (size_t i = 0; i < pixel_data_size / 2; i++)
    {
      char c = b[off + i];
      pixel_data[i * 2] = (c >> 4) & 0xF;
      pixel_data[i * 2 + 1] = c & 0xF;
    }
  }

  delete[] b;

}

Image::~Image()
{
  delete pixel_data;
  delete color_table;
}

void Image::save(std::string out_path)
{
  std::ofstream o(out_path, std::ios::binary);

  o.put('B');
  o.put('M');
  uint32_to_out(o, f_size);
  o.put(0);
  o.put(0);
  o.put(0);
  o.put(0);
  uint32_to_out(o, f_off_bits);

  uint32_to_out(o, i_size);
  uint32_to_out(o, i_width);
  uint32_to_out(o, i_height);

  o.put(1);
  o.put(0);

  uint16_to_out(o, i_bit_count);
  uint32_to_out(o, i_compression);
  uint32_to_out(o, i_size_image);
  uint32_to_out(o, i_x_pix_meter);
  uint32_to_out(o, i_y_pix_meter);
  uint32_to_out(o, i_color_used);
  uint32_to_out(o, i_color_important);

  for (size_t i = 0; i < color_table_size; i++)
  {
    color_to_out(o, color_table[i]);
  }

  if (i_bit_count == 4)
  {
    for (size_t i = 0; i < pixel_data_size; i += 2)
    {
      char c = pixel_data[i + 1];
      c |= pixel_data[i] << 4;
      o.put(c);
    }
  }
}
