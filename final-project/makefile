main: main.o node.o stack.o iha.o
	g++ -o main main.o node.o stack.o iha.o

main.o: main.cpp node.h stack.h iha.h
	g++ -c $(CFLAGS) main.cpp

node.o: node.cpp node.h
	g++ -c $(CFLAGS) node.cpp

stack.o: stack.cpp stack.h
	g++ -c $(CFLAGS) stack.cpp

iha.o: iha.cpp iha.h
	g++ -c $(CFLAGS) iha.cpp

clean:
	rm -rf *.o main