#pragma once
#include <iostream>
#include <vector>
#include <Ice/Ice.h>
#include <vlc/vlc.h>
#include <ServeurIce.h>

using namespace server ;

class launcher : public ServeurIce {
    private :
        static int cpt ;
        bdd bdd_;
        libvlc_instance_t *vlc = NULL;

    public:
        launcher(const int size = 0);
        ~launcher();
        void ajout(::server::Musique m) ;
        void jouerMusique(int id, const ::Ice::Current&);
        bool ajouterMusique(std::string name, const ::Ice::Current&);
        void display(const ::Ice::Current&);
        ::server::bdd getBdd(const ::Ice::Current&);
};