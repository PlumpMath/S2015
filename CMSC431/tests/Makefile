COMPILER := ../Proj1
NASM := nasm -f elf64
CFLAGS := -o
CC := gcc
SHELL := /bin/sh

srcdir = src
objdir = obj
asmdir = asm

TESTS = $(wildcard $(srcdir)/*)
EXECUTABLES = $(addsuffix .out, $(notdir $(TESTS)))

asmpath = $(asmdir)/$(^F).asm
objpath = $(objdir)/$(^F).o

.PHONY: all
all: $(EXECUTABLES)

$(EXECUTABLES): %.out: src/%
ifeq ($(MAKELEVEL), 0)
	$(error Tests cannot be made directly)
else
	$(COMPILER) < $^ > $(asmpath)
	$(NASM) $(asmpath) -o $(objpath)
	$(CC) $(objpath) $(CFLAGS) $@
endif

.PHONY: clean
clean:
	-$(RM) $(asmdir)/*asm $(objdir)/*.o *.out
