CXX := g++ -g
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main : ./bin/main.exe

./bin/main.exe : ./bin/main.o ./bin/SnakeGUI.o 
	$(CXX) -o ./bin/main.exe ./bin/main.o ./bin/SnakeGUI.o $(LDFLAGS)

./bin/main.o : ./src/main.cpp
	$(CXX) -c ./src/main.cpp -o ./bin/main.o

./bin/SnakeGUI.o : ./src/SnakeGUI.cpp ./src/SnakeGUI.h
	$(CXX) -c ./src/SnakeGUI.cpp -o ./bin/SnakeGUI.o

clean :
	rm -f ./bin/*.o ./bin/*.exe