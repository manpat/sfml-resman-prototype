LIBS=-llua

build: *.cpp
	g++ -std=c++11 $^ -o build

run: build
	@./build