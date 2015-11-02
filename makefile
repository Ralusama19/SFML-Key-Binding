LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

all:
	g++ -c main.cc
	g++ main.o -o prova $(LIBS)

clean:
	rm -f prova main.o

