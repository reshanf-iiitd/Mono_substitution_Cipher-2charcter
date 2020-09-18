# Makefile for the assignment

# GNU C++ Compiler
CC=g++

# Use C++11 standard
CFLAGS=--std=c++11

all: keygen encrypt decrypt codebreaker

keygen: keygen.cpp
	$(CC) $(CFLAGS) keygen.cpp -o keygen

encrypt: encrypt.cpp
	$(CC) $(CFLAGS) encrypt.cpp -o encrypt

decrypt: decrypt.cpp
	$(CC) $(CFLAGS) decrypt.cpp -o decrypt

codebreaker: codebreaker.cpp
	$(CC) $(CFLAGS) codebreaker.cpp -o codebreaker
