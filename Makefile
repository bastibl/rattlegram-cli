
CXXFLAGS = -std=c++17 -W -Wall -Ofast -fno-exceptions -fno-rtti -Wno-vla-cxx-extension -g
CXX = clang++ -stdlib=libc++ -march=native
CXX = clang++ -march=native

#CXX = armv7a-hardfloat-linux-gnueabi-g++ -static -mfpu=neon -march=armv7-a
#QEMU = qemu-arm

.PHONY: all

all: encode decode

encode: ./src/encode.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

decode: ./src/decode.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f encode && rm -f decode

