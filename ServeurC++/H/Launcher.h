#pragma once
#include <iostream>
#include <vector>
#include <Ice/Ice.h>
#include <vlc/vlc.h>
#include <ServeurIce.h>

using namespace server ;

/**
 * Classe du serveur ICE
 * Pensez à ne pas oublier de mettre les fonctions que vous avez déclarés dans votre
 * fichier ICE.
 * ATTENTION : Pensez à mettre --> const ::Ice::Current&
 * dans chaque fonction qui est connu du serveur ICE
**/
class Launcher : public ServeurIce {
    private :
        static int cpt ;
        //Correspond à ce qu'il y a dans le fichier ServeurIce.ice "sequence"
        bdd bdd_;
        libvlc_instance_t *lecteurMusique = NULL;

    public:
        Launcher(const int size = 0);
        ~Launcher();
        void ajout(::server::Musique m) ;
        void jouerMusique(int id, const ::Ice::Current&);
        bool stopMusique(const ::Ice::Current&) ;
        bool ajouterMusique(std::string name, const ::Ice::Current&);
        void display(const ::Ice::Current&);
        ::server::bdd getBdd(const ::Ice::Current&);
};