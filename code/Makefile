all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	g++  $< -o $@ -std=gnu++14 -lGL -lGLU -lglut -lgraph
