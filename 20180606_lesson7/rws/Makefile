CC            = gcc #-pthread
CFLAGS 	      = -pthread
RM            = rm -fr

all: rws dist doc

#regole predefinite (vedi make -p):
#LINK.c   = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
#LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
#LINK.cpp = $(LINK.cc)
#%: %.c   ; $(LINK.c)   $^ $(LOADLIBES) $(LDLIBS) -o $@
#%: %.cpp ; $(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean: ; $(RM)  mysh  doc/

dist:  ; $(PACKAGE)-$(VERSION)/rws.c \
	$(PACKAGE)-$(VERSION)/Makefile \
	$(PACKAGE)-$(VERSION)/Doxyfile 

doc:   apidoc
apidoc: Doxyfile ; mkdir -p docs;  doxygen
