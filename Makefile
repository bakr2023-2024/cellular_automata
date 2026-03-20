main: main.cpp automata.cpp
	g++ --std=c++20 -o main main.cpp automata.cpp -lraylib -lopengl32 -lgdi32 -lwinmm