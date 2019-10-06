cmake_minimum_required(VERSION 3.14)

project(bmpglitch)

add_compile_options(-Wall)
add_compile_options(-Wextra -Wpedantic)
add_compile_options(-fmessage-length=80 -fno-diagnostics-show-option)
add_compile_options(-fstack-protector-all -g -O3 -std=c++14 -Walloc-zero)
add_compile_options(-Walloca -Wctor-dtor-privacy -Wduplicated-cond)
add_compile_options(-Wduplicated-branches -Werror -Wfatal-errors -Winit-self)
add_compile_options(-Wlogical-op -Wold-style-cast -Wshadow)
add_compile_options(-Wunused-const-variable=1 -Wzero-as-null-pointer-constant)

if($ENV{LOG_DEBUG})
add_compile_definitions(LEVEL_DEBUG)
endif()
if($ENV{LOG_INFO})
add_compile_definitions(LEVEL_INFO)
endif()
if($ENV{LOG_WARN})
add_compile_definitions(LEVEL_WARN)
endif()
if($ENV{LOG_ERROR})
add_compile_definitions(LEVEL_ERROR)
endif()

add_executable(
  ${PROJECT_NAME}
  main.cpp
  logger/logger.cpp
  usage/usage.cpp
  arguments/arguments.cpp
  Bitmap/Bitmap.cpp
)
