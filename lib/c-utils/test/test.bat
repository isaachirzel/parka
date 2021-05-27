@echo off

clang main.c -I../include -std=c99 -pedantic -Wall -Wextra -o main.exe && main.exe
