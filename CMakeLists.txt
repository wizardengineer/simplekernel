cmake_minimum_required(VERSION 3.11...3.19)

project(simplekernel)

include(cmake/HelpingFunctions.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  # include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

set(CMAKE_C_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

# setting current dir for easy use
set(CRT_DIR ${CMAKE_CURRENT_LIST_DIR})

# setting link.ld
set(CMAKE_LINKER_FILE "${CRT_DIR}/smkrnl/arch/i386/linker.ld")
set(CMAKE_LINKER_FLAGS " -T ${CMAKE_LINKER_FILE} -melf_i386")

# setting the kernel files
add_subdirectory(smkrnl)
add_subdirectory(smkrnl/arch/i386)

target_link_libraries(kernel_file_object KERNEL_ASM_OBJECTS)

