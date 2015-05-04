CC=g++
SRCDIR=src
BUILDDIR=build
TARGET=bin/astar
TESTER=bin/ggen

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
	@echo "removing garbage"; rm -f *~ *#; rm -f ./src/*~ ./src/*#; rm -f ./include/*~ ./include/*#

tests:
	$(CC) gen/RandomGraph.cpp gen/UF.cpp -o $(TESTER)

graphs: tests
	$(TESTER) test/SmallGeo.txt 20 3 12
	$(TESTER) test/MedGeo.txt 100 3 12
	$(TESTER) test/LargeGeo.txt 500 3 12
	$(TESTER) test/SmallGrid.txt 20 13 12
	$(TESTER) test/MedGrid.txt 100 13 12
	$(TESTER) test/LargeGrid.txt 500 13 12
	$(TESTER) test/SmallTorus.txt 4 9 12
	$(TESTER) test/MedTorus.txt 10 9 12
	$(TESTER) test/LargeTorus.txt 22 9 12



.PHONY: clean test

again: clean $(TARGET)
