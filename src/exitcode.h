#ifndef EXITCODE_H_INCLUDE
#define EXITCODE_H_INCLUDE

enum exit_code : unsigned short
{
  success = 0,
  not_enough_arguments,
  invalid_option,
  invalid_bmp_file,
  other,
};

#endif /* EXITCODE_H_INCLUDE */