all:
	gcc -c biblioteca.c -lSDL -lSDL_gfx  
	gcc mp4.c -o mp4 biblioteca.o -lSDL -lSDL_gfx 

clean:
	rm -rf *.o mp4
