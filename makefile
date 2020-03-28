CXXFLAGS=-std=c++11 -I ServeurC++/H -DICE_CPP11_MAPPING

serveurMP3 : ServeurC++/O/Main.o ServeurC++/O/Server.o ServeurC++/O/IServer.o
	g++ -o serveurMP3 -g $^ -lIce++11 -lvlc -pthread

ServeurC++/O/Main.o : ServeurC++/C/Main.cpp
	g++ ${CXXFLAGS} -o ServeurC++/O/Main.o -c $<

ServeurC++/O/Server.o : ServeurC++/C/Launcher.cpp ServeurC++/H/Launcher.h
	g++ ${CXXFLAGS} -o ServeurC++/O/Server.o -c $<

ServeurC++/O/IServer.o : ServeurC++/C/ServeurIce.cpp ServeurC++/H/ServeurIce.h
	g++ ${CXXFLAGS} -o ServeurC++/O/IServer.o -c $<

Client :
	python python/Client.py

ice:
	slice2cpp ServeurIce.ice
	mv ServeurIce.cpp ServeurC++/C/
	mv ServeurIce.h ServeurC++/H/
	slice2py ServeurIce.ice
	mv ServeurIce_ice.py python/

clean:
	rm ServeurC++/O/*.o

mrPropre: clean
	rm serveurMP3

install:
	sudo apt-get install zeroc-ice-all-runtime zeroc-ice-all-dev
	sudo apt-get install libvlccore-dev