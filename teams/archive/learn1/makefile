
east.o: main.c ../../soccer.h ../../players.h hash.h situation.h
	g++ -I../.. -c -DEAST_TEAM main.c -o east.o

west.o: main.c ../../soccer.h ../../players.h hash.h situation.h
	g++ -I../.. -c -DWEST_TEAM main.c -o west.o

hash.o: hash.cpp ../../soccer.h ../../players.h hash.h
	g++ -I../.. -c hash.cpp -o hash.o

situation.o: situation.cpp ../../soccer.h ../../players.h situation.h hash.h
	g++ -I../.. -c situation.cpp -o situation.o

libeast.a: east.o hash.o situation.o
	ar rc libeast.a east.o 

libwest.a: west.o hash.o situation.o
	ar rc libwest.a west.o 

libcommon.a: situation.o hash.o
	ar rc libcommon.a hash.o situation.o

clean: 
	rm -f *.o
	rm -f *.a
	rm -f core
