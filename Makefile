CXX := g++ -g
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main : ./bin/main.exe

./bin/main.exe : ./bin/main.o ./bin/SnakeGUI.o ./bin/SnakeLogic.o
	$(CXX) -o ./bin/main.exe ./bin/main.o ./bin/SnakeGUI.o ./bin/SnakeLogic.o $(LDFLAGS)

./bin/main.o : ./src/main.cpp
	$(CXX) -c ./src/main.cpp -o ./bin/main.o

./bin/SnakeGUI.o : ./src/SnakeGUI.cpp ./src/SnakeGUI.h
	$(CXX) -c ./src/SnakeGUI.cpp -o ./bin/SnakeGUI.o

./bin/SnakeLogic.o : ./src/SnakeLogic.cpp ./src/SnakeLogic.h
	$(CXX) -c ./src/SnakeLogic.cpp -o ./bin/SnakeLogic.o 

clean :
	rm -f ./bin/*.o ./bin/*.exe