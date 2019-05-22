CXX=g++
CXXFLAGS=-o3
LDFLAGS=-I. -I./smhasher/src -L.
LIB=libbloom.so

all: test $(LIB)

$(LIB): BloomFilter.hpp BloomFilter.cpp smhasher/src/MurmurHash3.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC BloomFilter.cpp smhasher/src/MurmurHash3.cpp \
		-o $@ $(LDFLAGS)

test: $(LIB) test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o $@ $(LDFLAGS) -lbloom

run: test
	LD_LIBRARY_PATH=. ./test

clean:
	$(RM) -f $(LIB)
	$(RM) -f test
