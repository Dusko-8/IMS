# Define the compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = -g -O2 -Wall -std=c++11

LDFLAGS= -lsimlib -lm
# Define the source files
SRC = simulation.cpp visitor.cpp visitor_generator.cpp SkyResort_Data.cpp

# Define the output executable
OUT = simulation

# Define the compile command
all: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

# Define the clean command
clean:
	rm -f $(OUT)
