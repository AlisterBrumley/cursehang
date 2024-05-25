# IDIR =../include
CC=clang
CFLAGS= -lncurses

SRCDIR		= src
INCLDIR		= include
OUTFILE		= cursehang

SOURCES		:= $(wildcard $(SRCDIR)/*.c)
INCLUDES	:= $(wildcard $(INCLDIR)/*.h)


UNAME_S		:= $(shell uname -s)
UNAME_M		:= $(shell uname -m)

$(OUTFILE): $(SOURCES) $(INCLUDES)
		@mkdir -p $(UNAME_S)_$(UNAME_M)
		@$(CC) -I $(INCLDIR) -o $(UNAME_S)_$(UNAME_M)/$(OUTFILE) $(SOURCES) $(CFLAGS)
		@echo "made file in $(UNAME_S)_$(UNAME_M)/"