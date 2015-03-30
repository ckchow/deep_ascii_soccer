east.o: main.c ../../soccer.h ../../players.h 
	g++ -I../.. -c -DEAST_TEAM main.c -o east.o

west.o: main.c ../../soccer.h ../../players.h 
	g++ -I../.. -c -DWEST_TEAM main.c -o west.o

common.o: common.c ../../soccer.h ../../players.h 
	g++ -I../.. -c -DWEST_TEAM common.c -o common.o

libwest.a: west.o
	ar rc libwest.a west.o
	ranlib libwest.a

libeast.a: east.o
	ar rc libeast.a east.o
	ranlib libeast.a

libcommon.a: common.o
	ar rc libcommon.a common.o
	ranlib libcommon.a

clean: 
	rm -f *.o
	rm -f *.a
	rm -f core
