CC=g++
SRCDIR=src
BUILDDIR=build
TARGET=bin/astar

SRCEXT=cpp
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS=-Wall -g -std=c++11
INC=-I include
LIB=
 
$(TARGET): $(OBJECTS) 
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) bin/ggen"; $(RM) -r $(BUILDDIR) $(TARGET); $(RM) bin/ggen

tests:
	$(CC) gen/RandomGraph.cpp gen/UF.cpp -o bin/ggen

.PHONY: clean test

