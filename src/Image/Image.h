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
};

#endif /* IMAGE_H_INCLUDE */