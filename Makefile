CC=g++
SRCDIR=src
BUILDDIR=build
TARGET=bin/astar
TESTER=bin/ggen
TARGET=astar

SRCEXT=cpp
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS=-Wall -g -std=c++11
INC=-I include
LIB=
 
$(TARGET): $(OBJECTS) 
	@echo " Linking..."
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) ggen"; $(RM) -r $(BUILDDIR) $(TARGET); $(RM) ggen
	@echo "removing garbage"; rm -f *~ *#; rm -f ./src/*~ ./src/*#; rm -f ./include/*~ ./include/*#

tests:
	$(CC) gen/RandomGraph.cpp gen/UF.cpp -o $(TESTER)

graphs: tests
	$(TESTER) test/SmallGeo.txt 1000 3 0
	$(TESTER) test/MedGeo.txt 5000 3 0
	$(TESTER) test/LargeGeo.txt 15000 3 0
	$(TESTER) test/SmallGrid.txt 1000 13 12
	$(TESTER) test/MedGrid.txt 5000 13 12
	$(TESTER) test/LargeGrid.txt 15000 13 12
	$(TESTER) test/SmallTorus.txt 32 9 12
	$(TESTER) test/MedTorus.txt 71 9 12
	$(TESTER) test/LargeTorus.txt 122 9 12
	$(TESTER) test/UniformGrid.txt 100 13 0

	$(CC) gen/RandomGraph.cpp gen/UF.cpp -o ggen

.PHONY: clean test

again: clean $(TARGET)
