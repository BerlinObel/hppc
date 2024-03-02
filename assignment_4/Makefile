CXX := clang++-12
CXX := g++ 

#######################################################
# Optimization flags are chosen as the last definition.
# Comment out using "#" at the begining of the line or rearrange according to your needs.
#
# Fastest executable (-ffast-math removes checking for NaNs and other things)
OPT=-O3 -ffast-math

# Profiling
# OPT=-O3 -ffast-math -pg -g -Og

# Add thread checking to code
#OPT=-O1 -fsanitize=thread -fPIE -pie

# Faster compilation time
#OPT=-O1

CXXFLAGS := $(OPT) -Wall -march=native -g -std=c++14

default: seq mp mp_weak mp_strong

seq: seismogram_seq.cpp
	$(CXX) seismogram_seq.cpp $(CXXFLAGS) -o seq

mp: seismogram_omp.cpp
	$(CXX) seismogram_omp.cpp $(CXXFLAGS) -fopenmp -o mp

mp_weak: seismogram_omp_weak.cpp
	$(CXX) seismogram_omp_weak.cpp $(CXXFLAGS) -fopenmp -o mp_weak

mp_strong: seismogram_omp_strong.cpp
	$(CXX) seismogram_omp_strong.cpp $(CXXFLAGS) -fopenmp -o mp_strong

clean:
	rm -fr seq mp mp_weak mp_strong
