COMPILE := g++ -std=c++14 -c
LINK := g++ -o


all:
	make compile
	make link

clean:
	rm -f build/*.o
	rm -f bin/*

compile:
	make timer.o
	make associative.o
	make fifo.o
	make lifo.o
	make sequential.o

link:
	make associative
	make fifo
	make lifo
	make sequential

run:
	bin/associative
	bin/fifo
	bin/lifo
	bin/sequential


associative.o:
	$(COMPILE) associative.cpp -o build/associative.o

fifo.o:
	$(COMPILE) -c fifo.cpp -o build/fifo.o

lifo.o:
	$(COMPILE) lifo.cpp -o build/lifo.o

sequential.o:
	$(COMPILE) -c sequential.cpp -o build/sequential.o

timer.o:
	$(COMPILE) timer.cpp -o build/timer.o


associative: timer.o associative.o
	$(LINK) bin/associative build/associative.o build/timer.o

fifo: timer.o fifo.o
	$(LINK) bin/fifo build/fifo.o build/timer.o

lifo: timer.o lifo.o
	$(LINK) bin/lifo build/lifo.o build/timer.o

sequential: timer.o sequential.o
	$(LINK) bin/sequential build/sequential.o build/timer.o
