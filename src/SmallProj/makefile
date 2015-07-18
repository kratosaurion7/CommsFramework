CC=clang++
CFLAGS=-c -emit-llvm -ferror-limit=1 --std=c++0x
FILES=*.cpp

CPPHEADERS=E:\MinGW\mingw32\lib\gcc\mingw32\4.8.1\include\c++
CPPHEADERS2=E:\MinGW\lib\gcc\mingw32\4.8.1\include\c++\mingw32


CHEADERS=E:\MinGW\mingw32\lib\gcc\mingw32\4.8.1\include
MINGWHEADERS=E:\MinGW\include
MINGWBITSHEADER=E:\MinGW\lib\gcc\mingw32\4.8.1\include\c++\mingw32


build:
    $(CC) $(CFLAGS) -I $(CPPHEADERS) -I $(CPPHEADERS2) $(FILES)