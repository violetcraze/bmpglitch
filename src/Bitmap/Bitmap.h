#ifndef BITMAP_H_INCLUDE
#define BITMAP_H_INCLUDE

#include <fstream>
#include <iostream>
#include <vector>
#include "../logger/logger.h"
#include "../exitcode.h"

class Bitmap
{
  public:
    Bitmap(std::string bmp_path);
    ~Bitmap();
    void save(std::string out_path);

  struct Color
  {
    char r;
    char b;
    char g;
    Color() = default;
    Color(const Color&) = default;
    ~Color() = default;
  };

  private:
    uint32_t f_size;
    uint32_t f_off_bits;

    uint32_t i_size;
    uint32_t i_width;
    uint32_t i_height;
    uint16_t i_bit_count;
    uint32_t i_compression;
    uint32_t i_size_image;
    uint32_t i_x_pix_meter;
    uint32_t i_y_pix_meter;
    uint32_t i_color_used;
    uint32_t i_color_important;

    size_t color_table_size;
    Bitmap::Color* color_table;

    size_t pixel_data_size;
    char* pixel_data;

};

#endif /* BITMAP_H_INCLUDE */