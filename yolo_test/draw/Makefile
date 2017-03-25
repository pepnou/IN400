all: draw
	

draw: draw.o
	gcc -Wall -g -o draw draw.o `sdl-config --libs` -lm -lSDL_ttf
	

draw.o: draw.c
	gcc -c `sdl-config --cflags` draw.c
	
run: all
	./draw

clean:
	rm -f draw.o
	rm -f draw
