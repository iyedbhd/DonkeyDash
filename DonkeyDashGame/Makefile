prog:fonctions.o main.o
	gcc fonctions.o main.o -o prog -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
main.o:main.c
	gcc -c main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
fonctions.o:fonctions.c
	gcc -c fonctions.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
