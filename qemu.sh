#!/bin/bash


if [ $1 == "clean" ] 
then
  # checking if it may need to clean
  echo "cleaning rn..."
  if [ -d "CMakeFiles/" ]
  then
    rm -rf "smkrnl/arch/i386/CMakeFiles/"
    rm -rf "smkrnl/CMakeFiles/" 
    rm -rf "CMakeFiles/"
    rm "CMakeCache.txt"
  fi

  if [ -d "grub/boot/*.elf" ] 
  then
    rm -rf "grub/boot/*.elf"
  fi

else
  echo "Unknown command"
fi
