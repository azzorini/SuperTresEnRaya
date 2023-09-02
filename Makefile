CC=g++
CFLAGS=-std=c++23 -Wall -Wextra -O2

PartidaSuperTresEnRaya: TresEnRaya.o SuperTresEnRaya.o PartidaSuperTresEnRaya.cpp
	$(CC) $(CFLAGS) PartidaSuperTresEnRaya.cpp TresEnRaya.o SuperTresEnRaya.o -o PartidaSuperTresEnRaya

SuperTresEnRaya.o: TresEnRaya.o SuperTresEnRaya.hpp SuperTresEnRaya.cpp
	$(CC) $(CFLAGS) -c SuperTresEnRaya.cpp

TresEnRaya.o: TresEnRaya.hpp TresEnRaya.cpp
	$(CC) $(CFLAGS) -c TresEnRaya.cpp

clean:
	rm TresEnRaya.o SuperTresEnRaya.o PartidaSuperTresEnRaya
