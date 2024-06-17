CC 				:= cc
CFLAGS 			:= -lncurses

SRCDIR			:= src
INCLDIR			:= include
NCDIR			:= /mingw64/include/ncurses

SOURCES			:= $(wildcard $(SRCDIR)/*.c)
INCLUDES		:= $(wildcard $(INCLDIR)/*.h)


# CHECK PLATFORM, ADD WINDOWS VARS
ifeq ($(OS),Windows_NT)
	CFLAGS 		+= -DNCURSES_STATIC
	INCLUDES	+= $(wildcard $(NCDIR)/*.h)
	OS 			:= Win
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
	OS		:= $(shell uname -s)
	ARCH	:= $(shell uname -m)
endif

OUTFILE		= $(OS)_$(ARCH)/cursehang

$(OUTFILE): $(SOURCES) $(INCLUDES)
		@mkdir -p $(OS)_$(ARCH)
		@$(CC) -I $(INCLDIR) -o $(OUTFILE) $(SOURCES) $(CFLAGS)
		@echo "made file in $(OS)_$(ARCH)/"