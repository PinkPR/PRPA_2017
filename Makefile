CFLAGS = -std=c++11 -I/usr/local/Cellar/libsndfile/1.0.26/include -L/usr/local/Cellar/libsndfile/1.0.26/lib -L/usr/local/lib

LIBS = `pkg-config --libs opencv`

SRC = main.cpp reader.cc writer.cc audio.cc kernel.cc light.cc

all:
	clang++ $(CFLAGS) -g $(SRC) $(LIBS) -lsndfile -ltbb -o vefa

clean:
	rm vefa
