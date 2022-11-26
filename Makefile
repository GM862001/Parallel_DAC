BINDIR = ./bin/
INCDIRS = ./include/
SOURCEDIR = ./src/
BUILDDIR = ./build/
CONFIG_FILE = config.cfg

CXX = g++
DEPFLAGS = -MP -MD
CXXFLAGS = $(foreach D, $(INCDIRS), -I$(D)) -O3 -std=c++17 $(DEPFLAGS) -Wall -Wextra
LDFLAGS = -pthread

SOURCES = $(wildcard $(SOURCEDIR)*.cpp)
DEPFILES = $(patsubst $(SOURCEDIR)%.cpp, $(BUILDDIR)%.d, $(SOURCES))

BIN1 = $(BINDIR)Experiment1
OBJ1 = $(patsubst %, $(BUILDDIR)%.o, Experiment1 Mergesort utimer utils)

BIN2 = $(BINDIR)Experiment2
OBJ2 = $(patsubst %, $(BUILDDIR)%.o, Experiment2 Mergesort utimer utils)

BIN3 = $(BINDIR)measure_Tnw
OBJ3 = $(patsubst %, $(BUILDDIR)%.o, measure_Tnw utimer utils)

BIN4 = $(BINDIR)run
OBJ4 = $(patsubst %, $(BUILDDIR)%.o, run Mergesort utimer utils)

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)
	
$(BIN1): $(OBJ1)
	$(CXX) -o $@ $(OBJ1) $(LDFLAGS)

$(BIN2): $(OBJ2)
	$(CXX) -o $@ $(OBJ2) $(LDFLAGS)

$(BIN3): $(OBJ3)
	$(CXX) -o $@ $(OBJ3) $(LDFLAGS)

$(BIN4): $(OBJ4)
	$(CXX) -o $@ $(OBJ4) $(LDFLAGS)

$(BUILDDIR)%.o: $(SOURCEDIR)%.cpp $(CONFIG_FILE)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINDIR)* $(BUILDDIR)*


-include $(DEPFILES)

.PHONY: all clean
