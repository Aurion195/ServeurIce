CXX=g++
CXXFLAGS=-std=c++11 -I ServeurC++/H -DICE_CPP11_MAPPING
LDFLAGS=-lIce++11 -lvlc -pthread

dir=ServeurC++/
dirpy=python/
dirjava=java/
headers=H/
src=C/
obj=O/
projet=serv

${projet} : ${dir}${obj}main.o ${dir}${obj}Server.o ${dir}${obj}IServer.o
	${CXX} -o ${projet} -g $^ ${LDFLAGS}

${dir}${obj}main.o : ${dir}${src}Main.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $<

${dir}${obj}Server.o : ${dir}${src}launcher.cpp ${dir}${headers}launcher.h
	${CXX} ${CXXFLAGS} -o $@ -c $<

${dir}${obj}IServer.o : ${dir}${src}ServeurIce.cpp ${dir}${headers}ServeurIce.h
	${CXX} ${CXXFLAGS} -o $@ -c $<

ice:
	slice2cpp ServeurIce.ice
	mv ServeurIce.cpp ServeurC++/C/
	mv ServeurIce.h ServeurC++/H/
	slice2py ServeurIce.ice
	mv ServeurIce_ice.py python/

clean:
	rm -rf ServeurC++/O/