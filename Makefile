CC = g++
OBJ =  ./src/client.o ./src/destination.o ./src/fragment.o ./src/star.o ./src/entity.o ./src/player.o ./src/space.o ./src/game.o ./src/platform.o ./src/building.o ./src/main.o

# allegro lib
#LIBS = `pkg-config --libs allegro-5.1 allegro_image-5.1 allegro_audio-5.1 allegro_acodec-5.1 allegro_primitives-5.1 allegro_ttf-5.1` libmeh.so
LIBS = `pkg-config --libs allegro-debug-5.0 allegro_image-debug-5.0 allegro_audio-debug-5.0 allegro_acodec-debug-5.0 allegro_primitives-debug-5.0 allegro_ttf-debug-5.0` libmeh.so
#static
#LIBS = -L/usr/local/lib `pkg-config --libs allegro-static-5.0 allegro_image-static-5.0 allegro_audio-static-5.0 allegro_acodec-static-5.0 allegro_primitives-static-5.0 allegro_ttf-static-5.0` libmeh.a
INCS = -I/usr/include -I./include/ -I./include/meh/

CFLAGS = -g -Wall -O3 $(INCS) -D_REENTRANT -std=c++0x

all: galactictaxi 

clean:
	rm -rf galactictaxi $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

galactictaxi: $(OBJ) $(LOBJ)
	$(CC) $(OBJ) $(LIBS) -o $@


