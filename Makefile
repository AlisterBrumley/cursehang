CC 				:= cc
CFLAGS 			:= -lncurses
INFLAGS 		= -I$(INCLDIR)

SRCDIR			:= src
INCLDIR			:= include
NCDIR			:= /mingw64/include/ncurses

SOURCES			:= $(wildcard $(SRCDIR)/*.c)
INCLUDES		:= $(wildcard $(INCLDIR)/*.h)


# CHECK PLATFORM, ADD WINDOWS VARS
ifeq ($(OS),Windows_NT)
	CFLAGS 		+= -DNCURSES_STATIC
	INCLUDES	+= $(wildcard $(NCDIR)/*.h)
	INFLAGS		+= -I$(NCDIR)
	OS 			:= Win
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        ARCH	:= x86_64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            ARCH	:= x86_64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            ARCH	:= x86
        endif
    endif
else
	OS		:= $(shell uname -s)
	ARCH 	:= $(shell uname -m)
endif

# ARCH	:= $(shell uname -m)

OUTFILE		= $(OS)_$(ARCH)/cursehang

$(OUTFILE): $(SOURCES) $(INCLUDES)
		@mkdir -p $(OS)_$(ARCH)
		@$(CC) $(INFLAGS) -o $(OUTFILE) $(SOURCES) $(CFLAGS)
		@echo "made file in $(OS)_$(ARCH)/"