CXX := g++

#######################################################
# Optimization flags are chosen as the last definition.
# Comment out using "#" at the begining of the line or rearrange according to your needs.
#
# Fastest executable (-ffast-math removes checking for NaNs and other things)
OPT=-O3 -ffast-math -pg

# Add profiling to code
# OPT=-O1 -pg

# Faster compilation time
# OPT=-O1

CXXFLAGS := $(OPT) -Wall -march=znver1 -g -std=c++14

default: seq vec vec_pragma

seq: Water_sequential.cpp
	$(CXX) Water_sequential.cpp $(CXXFLAGS) -o seq

vec: Water_vectorised.cpp
	$(CXX) Water_vectorised.cpp $(CXXFLAGS) -fopenmp-simd -fopt-info-vec-optimized  -o vec

vec_pragma: Water_vectorised_pragma.cpp
	$(CXX) Water_vectorised_pragma.cpp $(CXXFLAGS) -fopenmp-simd -fopt-info-vec-optimized  -o vec_pragma


clean:
	rm -fr seq vec vec_pragma
