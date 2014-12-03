LIBS=-llua -ldl -lsfml-graphics -lsfml-window -lsfml-system

build: *.cpp
	g++ -std=c++11 $^ -o build $(LIBS)

run: build
	@./build