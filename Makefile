crawler : main.o crawler.o config.o ctext.o tcpmanager.o
	g++ -o crawler main.o crawler.o config.o ctext.o tcpmanager.o

main.o : main.cpp crawler.h ctext.h config.h
	g++ -c main.cpp

crawler.o : crawler.cpp tcpmanager.h config.h base.h
	g++ -c crawler.cpp

ctext.o : ctext.cpp 
	g++ -c ctext.cpp

config.o : config.cpp base.h ctext.h
	g++ -c config.cpp

tcpmanager.o : tcpmanager.cpp 


.IGNORE : clean
.PHONY : clean
clean:
	-rm crawler *.o