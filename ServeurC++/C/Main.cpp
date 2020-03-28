#include "Ice/Ice.h"
#include "Launcher.h"

using namespace std ;
using namespace server ;

int main(int argc, char* argv[]) {
    cout << "Lancement du serveur" << endl ;

    //Code obligatoire
    try {
        Ice::CommunicatorHolder ich(argc, argv) ;
        auto adapter = ich->createObjectAdapterWithEndpoints("ServeurAdapter", "tcp -h 192.168.1.98 -p 10000");
        auto servant = make_shared<Launcher>();
        adapter->add(servant, ::Ice::stringToIdentity("Serveur"));
        adapter->activate();
        cout << "............." << endl ;
        while(true)
            cin.get();

        ich->waitForShutdown();
    }
    catch(const exception& e) {
        cerr << e.what() << endl ;
        return 1;
    }
}