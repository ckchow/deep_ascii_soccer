soccer.o: soccer.c soccer.h players.h
	g++ -w -c soccer.c

soccer: soccer.o 
	g++ -w soccer.o -o soccer -L./ -lcurses -ltermcap -lm \
		-least -leastcommon -lwest -lwestcommon

soccerboth: soccer.o 
	g++ -w soccer.o -o soccer -L./ -lcurses -ltermcap -lm \
		-least -lcommon -lwest 

clean: 
	rm -f *.o
	rm -f *.a
	rm -f *.LCK
	rm -f */*.LCK
	rm -f */*/*.LCK
	rm -f soccer
	rm -f core
	cleanteams
