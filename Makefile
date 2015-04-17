#
# TODO: 
#
 

CC = g++ # This is the main compiler
# CC = clang --analyze # and comment out the linker last line for sanity
SRCDIR = src
BUILDDIR = build
TARGET = bin/Ludo
SRCEXT = cpp
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.cpp=.o)))
# OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -Wall -g
LIB = -lSOIL -lfreeglut -lglu32 -lopengl32
# INC := -I include

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIB)
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	del $(BUILDDIR)\*.o 
	del bin\*.exe

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(LIB) -o bin/tester

# Spikes
ticket:
	# $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket
	$(CC) $(CFLAGS) spikes/ticket.cpp $(LIB) -o bin/ticket

.PHONY: clean