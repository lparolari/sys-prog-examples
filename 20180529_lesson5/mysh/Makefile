#******************************************************************************#
#* MYSH	                                                                     *#
#******************************************************************************#
PACKAGE = mysh
VERSION = 0.1
RELEASE = 1

CC            = g++
CXX           = g++
CPPFLAGS      = -Wall 
RM            = rm -fr

all: mysh docs

#regole predefinite (vedi make -p):
#LINK.c   = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
#LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
#LINK.cpp = $(LINK.cc)
#%: %.c   ; $(LINK.c)   $^ $(LOADLIBES) $(LDLIBS) -o $@
#%: %.cpp ; $(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

mysh: mysh.o
docs: ; mkdir -p docs;  doxygen

clean: ; $(RM)  mysh  docs