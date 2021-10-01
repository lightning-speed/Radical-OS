#!/bin/bash

die(){
  printf "[ERROR] %s\n" "$1"
  exit 1
}

main(){
  local directories=(
    "Drivers"
    "System"
    "Graphics"
    "Timer"
    "FS"
    "App32"
    "Shell"
    "Mego-Runtime"
    "Terminal-Runtime"
    "Util"
  )
  printf "Cleaning\n"
  mkdir -p "bin" >/dev/null 2>&1 || die "Could not make directory"
  rm -rf "bin/"*.o
  printf "Building\n"
  nasm -f "elf32" "src/kernel_loader2.asm" -o "kernel_loader.o"
  gcc -m32 -c -I "src/." "src/kernel.c" -o "kernel.o"
  cd "bin" || die "Could not cd to bin"
  for directory in "${directories[@]}"; do
    gcc -m32 -fno-exceptions -ffreestanding -fshort-wchar -mno-red-zone -c -I "../src/." "../src/${directory}/"*.c
  done
  #cp ../kernel* ../build/
  #cp ./*.o ../build/
  ld ../kernel_loader.o ../kernel.o  *.o  -o kernel.e
  rm -rf -- "../"*.o || die "Could not remove object files"
  rm -rf -- *.o || die "Could not remove object files"
  objcopy -Felf32-i386 kernel.e kernel.elf
  rm -rf -- *.e || die "Could not remove object files"
  qemu-system-x86_64 -kernel "kernel.elf"
  cd .. || die "Could not cd to previous directory"
  rm -rf bin || die "Could not remove bin directory"
}

main "$@"
