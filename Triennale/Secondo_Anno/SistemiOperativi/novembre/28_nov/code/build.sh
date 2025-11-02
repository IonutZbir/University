#!/bin/sh

gcc copy_seek_oread.c -o copy_p
./copy_p inputFile.txt outputFile.txt $1 
