##	TESTED WITH MAC OS 10.13+ USING CLANG (as it responds to CC)
##	TESTED WITH FEDORA 40 + DEBIAN 12 USING GCC
##	TESTED WITH WINDOWS 10 USING MING64/GCC
##		WINDOWS COMPILE/LINK TIME IS SLOW FOR ME
##		GO GRAB A COFFEE!
##
##	UNTESTED WITH OTHER PLATFORMS!

# COMPILER AND FLAGS
CC					:= cc
CFLAGS				:= -O2
LDFLAGS				:= -lncurses
INFLAGS				= -I$(INCLDIR)

# FILE VARS
SRCDIR				:= src
INCLDIR				:= include
OBJDIR				:= obj
NCDIR				:= /mingw64/include/ncurses
OUTDIR				= $(OS)_$(ARCH)
OUTFILE				= $(OUTDIR)/cursehang
ZIPFILE				= $(OUTFILE)_$(OUTDIR) # extension added later

# REQUIRMENTS
SOURCES				:= $(wildcard $(SRCDIR)/*.c)
INCLUDES			:= $(wildcard $(INCLDIR)/*.h)
OBJECTS				:= $(OBJDIR)/backspace.o $(OBJDIR)/cursehang.o $(OBJDIR)/cursehelpers.o $(OBJDIR)/gamehelpers.o $(OBJDIR)/hanging.o $(OBJDIR)/picker.o $(OBJDIR)/turn.o


# CHECK PLATFORM, ADD WINDOWS VARS
ifeq ($(OS),Windows_NT)
	CFLAGS			+= -DNCURSES_STATIC
	LDFLAGS			+= -static
	INCLUDES		+= $(wildcard $(NCDIR)/*.h)
	INFLAGS			+= -I$(NCDIR)
	OS 				:= Win
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		ARCH		:= x86_64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			ARCH	:= x86_64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			ARCH	:= x86
		endif
	endif
else
	OS				:= $(shell uname -s)
	ARCH			:= $(shell uname -m)
endif

# SET ZIP FOR DIST TARGET
ifeq ($(OS), Win)
	ZIPFILE 		:= $(addsuffix .zip, $(ZIPFILE))
	COMP 			:= 7z
	COMPFLAGS 		:= a $(ZIPFILE) $(OUTFILE).exe
endif
ifeq ($(OS), Darwin) #HDIUTIL AUTOMATICALLY SETS EXTENSION
	COMP 			:= hdiutil
	COMPFLAGS 		:= create -ov -srcfolder $(OUTDIR) -volname "cursehang" $(ZIPFILE)
endif
ifeq ($(OS), Linux)
	ZIPFILE 		:= $(addsuffix .tar.xz, $(ZIPFILE))
	COMP			:= tar
	COMPFLAGS		:= -cJf $(ZIPFILE) -C $(OUTDIR) cursehang
endif
# IF YOU'RE USING ANOTHER OS, ADD IT HERE

# MAIN TARGET, THAT LINKS SEPERATE OBJECTS
$(OUTFILE): $(OBJECTS)
		@echo "linking $(OUTFILE)"
		@mkdir -p $(OS)_$(ARCH)
		@$(CC) $(INFLAGS) $(OBJECTS) -o $(OUTFILE) $(LDFLAGS)
		@echo "made $(OUTFILE)"

# SEPERATE OBJECT TARGETS
#	NOT USING STRAIGHT TO COMPILE, AS WINDOWS IS SLOW
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

# HELPER TARGETS
.PHONY: clean fullclean dist

clean:
		rm -rf $(OBJDIR)

fullclean: clean
		rm -rf $(OUTDIR)

dist: $(OUTFILE)
		$(COMP) $(COMPFLAGS)