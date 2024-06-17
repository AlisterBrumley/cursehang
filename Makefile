CC 				:= cc
LDFLAGS			:= -lncurses
INFLAGS 		= -I$(INCLDIR)

SRCDIR			:= src
INCLDIR			:= include
OBJDIR			:= obj
NCDIR			:= /mingw64/include/ncurses

SOURCES			:= $(wildcard $(SRCDIR)/*.c)
INCLUDES		:= $(wildcard $(INCLDIR)/*.h)
OBJECTS			:= $(OBJDIR)/backspace.o $(OBJDIR)/cursehang.o $(OBJDIR)/cursehelpers.o $(OBJDIR)/gamehelpers.o $(OBJDIR)/hanging.o $(OBJDIR)/picker.o $(OBJDIR)/turn.o


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

$(OUTFILE): $(OBJECTS)
		@echo "compiling $(OUTFILE)"
		@mkdir -p $(OS)_$(ARCH)
		@$(CC) $(INFLAGS) $(OBJECTS) -o $(OUTFILE) $(LDFLAGS)
		@echo "made file in $(OS)_$(ARCH)/"

$(OBJDIR)/backspace.o: $(SRCDIR)/backspace.c $(INCLUDES)
		@echo "compiling backspace"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/backspace.c -o $(OBJDIR)/backspace.o $(CFLAGS)

$(OBJDIR)/cursehang.o: $(SRCDIR)/cursehang.c $(INCLUDES)
		@echo "compiling cursehang"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/cursehang.c -o $(OBJDIR)/cursehang.o $(CFLAGS)

$(OBJDIR)/cursehelpers.o: $(SRCDIR)/cursehelpers.c $(INCLUDES)
		@echo "compiling cursehelpers"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/cursehelpers.c -o $(OBJDIR)/cursehelpers.o $(CFLAGS)

$(OBJDIR)/gamehelpers.o: $(SRCDIR)/gamehelpers.c $(INCLUDES)
		@echo "compiling gamehelpers"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/gamehelpers.c -o $(OBJDIR)/gamehelpers.o $(CFLAGS)

$(OBJDIR)/hanging.o: $(SRCDIR)/hanging.c $(INCLUDES)
		@echo "compiling hanging"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/hanging.c -o $(OBJDIR)/hanging.o $(CFLAGS)

$(OBJDIR)/picker.o: $(SRCDIR)/picker.c $(INCLUDES)
		@echo "compiling picker"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/picker.c -o $(OBJDIR)/picker.o $(CFLAGS)

$(OBJDIR)/turn.o: $(SRCDIR)/turn.c $(INCLUDES)
		@echo "compiling turn"
		@mkdir -p $(OBJDIR)
		@$(CC) $(INFLAGS) -c $(SRCDIR)/turn.c -o $(OBJDIR)/turn.o $(CFLAGS)

clean:
	rm -rf $(OBJDIR)
	