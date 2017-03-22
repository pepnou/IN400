all: dezoom
	

dezoom: dezoom.o
	gcc -Wall -g -o dezoom dezoom.o `sdl-config --libs` -lm -lSDL_ttf
	

dezoom.o: dezoom.c
	gcc -c `sdl-config --cflags` dezoom.c
	
run: all
	./dezoom

clean:
	rm -f dezoom.o
	rm -f dezoom
