cmake_minimum_required(VERSION 3.4.1)

add_library( ndk_file_crypt
             SHARED
             src/main/cpp/ndk_file_crypt.cpp )

 add_library( ndk_file_utils
              SHARED
              src/main/cpp/ndk_file_utils.cpp )

 include_directories(src/main/cpp/inc)


find_library(  log-lib
              log )

target_link_libraries( # Specifies the target library.
                       ndk_file_crypt
                       ndk_file_utils
                       ${log-lib} )
