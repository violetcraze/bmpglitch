#include "./lineending.h"

void glitch::lineending::apply(Bitmap& img)
{
  LINFO("Starting Line Ending Glitch");
  char* pixels = img.pixels();
  // setup
  std::vector<char> next;
  next.reserve(img.pixels_size());

  for (size_t i = 0; i < img.pixels_size(); i++)
  {
    next.push_back(pixels[i]);
  }

  LINFO("Setup done!");

  // adding to vector

  for (size_t i = 0; i < next.size(); i++)
  {
    if (next[i] == '\r')
    {
      next.insert(next.begin() + i, '\n');
      i++;
    }
  }

  // copy back to pixels
  LINFO("Copying back ...");
  for (size_t i = 0; i < img.pixels_size(); i++)
  {
    pixels[i] = next[i];
  }
  LINFO("Done!");
}