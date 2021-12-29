all: main.cpp PetriNet.cpp
	g++ -std=c++11 main.cpp PetriNet.cpp -o main

run: all
	./main

clean:
	rm main