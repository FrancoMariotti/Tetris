objects = Game.o utils.o Board.o Piece.o Texture.o BitmapFont.o Timer.o
bin_dir = bin

tetris: $(objects)
	g++ -std=c++11 main.cpp $(objects) -lSDL2 -lSDL2_Image -o $(bin_dir)/tetris
%.o:
	g++ -c -std=c++11 $(objects:.o=.cpp)

bin_dir:
	mkdir $(bin_dir)

run:
	./$(bin_dir)/tetris

format:
	clang-format -i *.cpp

.PHONY: clean

clean:
	rm $(bin_dir)/tetris *.o 
