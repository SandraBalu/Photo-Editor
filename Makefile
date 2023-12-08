# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
TARGETS=image_editor

build:
	$(CC) $(CFLAGS) $(SRCS) -o image_editor -lm

pack:
	zip -FSr 314CA_BaluSandra_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
