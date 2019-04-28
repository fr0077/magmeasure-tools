CXXFLAGS = -Wall -Wextra
LDFLAGS = -I/usr/local/Cellar/boost/1.69.0_2/include

all: meshgen.cpp e42region.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS)  e42region.cpp meshgen.cpp -o meshgen

