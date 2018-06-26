

SOURCES=$(wildcard src/*.cc)
OBJECTS=$(subst src,obj,$(subst cc,o,$(SOURCES)))
INCLUDE=-I. -Iinclude
EXE=modular
CXX=g++
CXXFLAGS=-std=c++17 -ldl -lstdc++fs

default: all
all: $(EXE)

.PHONY: pre-build

pre-build:
	@mkdir -p obj/

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<
