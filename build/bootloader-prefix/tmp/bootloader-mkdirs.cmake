# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif_5.0.6/v5.0.6/esp-idf/components/bootloader/subproject"
  "D:/For_study/ESP32S3/build/bootloader"
  "D:/For_study/ESP32S3/build/bootloader-prefix"
  "D:/For_study/ESP32S3/build/bootloader-prefix/tmp"
  "D:/For_study/ESP32S3/build/bootloader-prefix/src/bootloader-stamp"
  "D:/For_study/ESP32S3/build/bootloader-prefix/src"
  "D:/For_study/ESP32S3/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/For_study/ESP32S3/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/For_study/ESP32S3/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
