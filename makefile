CXX = g++
CXXFLAGS = -Wall -g

ZERO = zero_list
ONE = one_list

MAIN = cap
HANDLE = cmd_handler

$(MAIN) : $(MAIN).o $(HANDLE).o $(ZERO).o $(ONE).o
	$(CXX) $(CXXFLAGS) -o $(MAIN) $^

$(MAIN).o : $(MAIN).cpp
	$(CXX) $(CXXFLAGS) -c $(MAIN).cpp

$(HANDLE).o : $(HANDLE).cpp
	$(CXX) $(CXXFLAGS) -c $(HANDLE).cpp

$(ZERO).o : $(ZERO).cpp
	$(CXX) $(CXXFLAGS) -c $(ZERO).cpp

$(ONE).o : $(ONE).cpp
	$(CXX) $(CXXFLAGS) -c $(ONE).cpp

