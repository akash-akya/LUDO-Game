#
# TODO: 
#
 
CC = g++ # This is the main compiler
SRCDIR = src
BUILDDIR = build
TARGET = bin/Ludo
SRCEXT = cpp
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.cpp=.o)))
CFLAGS =-Wall -g -fno-stack-protector 
LIB = -lSOIL -lglut -lX11 -lGL -lGLU -lm
# INC := -I include

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIB)
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/*.h
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