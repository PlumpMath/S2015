COMPILER := ../Proj1
NASM := nasm -f elf64
CFLAGS := -lm -o
CC := gcc
SHELL := /bin/sh
MKDIR_P = mkdir -p

srcdir = src
objdir = obj
asmdir = asm

TESTS = $(wildcard $(srcdir)/*)
EXECUTABLES = $(addsuffix .out, $(notdir $(TESTS)))

asmpath = $(asmdir)/$(basename $(^F)).asm
objpath = $(objdir)/$(basename $(^F)).o

.PHONY: all
all: $(EXECUTABLES)

$(EXECUTABLES): %.out: src/%
ifeq ($(MAKELEVEL), 0)
	$(error Tests cannot be made directly)
else	
	$(MKDIR_P) $(objdir)
	$(MKDIR_P) $(asmdir)

	$(COMPILER) < $^ > $(asmpath)
	$(NASM) $(asmpath) -o $(objpath)
	$(CC) $(objpath) $(CFLAGS) $@
endif

.PHONY: clean
clean:
	-$(RM) $(asmdir)/*asm $(objdir)/*.o *.out
