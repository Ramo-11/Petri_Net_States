all: main.cpp
	g++ -std=c++11 main.cpp -o main

run: all
	./main

clean:
	rm main