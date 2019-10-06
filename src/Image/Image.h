#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <fstream>
#include <iostream>
#include "../logger/logger.h"
#include "../exitcode.h"

class Image
{
  public:
    Image(std::string bmp_path);

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
    
};

#endif /* IMAGE_H_INCLUDE */