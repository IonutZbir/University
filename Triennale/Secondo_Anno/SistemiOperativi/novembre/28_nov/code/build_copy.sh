#!/bin/sh

gcc copy_file_with_seek.c -o copy_seek
./copy_seek inputFile.txt outputFile.txt $1
