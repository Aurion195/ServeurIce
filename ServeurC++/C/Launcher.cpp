#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <Launcher.h>

using namespace std;
using namespace server;

/**
 * Compteur de musique, permet de les identifier par leurs ID
**/
int Launcher::cpt = 0 ;

/**
 * Constructeur du serveur, permet d'initialiser le vector de musique
 * @param size = taille du vecteur ;
**/
Launcher::Launcher(int size) {
    this->bdd_.resize(size) ;
}

/**
 * Destructeur du serveur
**/
Launcher::~Launcher() {

}

/**
 * Permet d'ajouter une musique à la liste de musique
 * Ajoute l'ID aussi en fonction du compteur
 * Musique est la structure que nous avons déclarer dans notre fichier ice
 * @param m = musique à ajouter ;
**/
void Launcher::ajout(Musique m) {
    m.id = cpt++;
    bdd_.push_back(m) ;
}

/**
 * Permet d'ajouter une musique au serveur en fonction de son nom
 * si le nom ne correspond pas à un fichier dans le repertoire musique
 * @param name = nom de la musique ;
 * @return true si le serveur peut ajouter la musique / false sinon ;
**/
bool Launcher::ajouterMusique(string name, const ::Ice::Current&) {
    const string nameFile = "Musique/" + name ;

    //Toutes mes chanson vont être délimiter de la même façon
    //titre&author, cela est plus facile pour le serveur
    string delimiter = "&" ;
    FILE *file = fopen(nameFile.c_str(), "r");

    if(file) {
        Musique m ;

        m.name = name.substr(0, name.find("&")) ;
        name.erase(0, name.find(delimiter) + delimiter.length()) ;

        m.artist = name.substr(0, name.find(".")) ;

        this->ajout(m) ;

        return true ;
    }

    return false ;
}

/**
 * Permet de jouer une musique sur le serveur
 * la page web correspond à :
 * ip + dst
 * dst correspond à ce qu'il y a, à la fin de la ligne 92
 * @param id = identifiant de la musique à jouer ;
**/
void Launcher::jouerMusique(int id, const ::Ice::Current&) {
    if(lecteurMusique == NULL) {
        if(id < 0) {
            cout << "Erreur numéro impossible" << endl ;
            return ;
        }

        Musique m ;

        for(int i = 0 ; i < bdd_.size() ; i++) {
            if(id == bdd_[i].id) {
                m = bdd_[i] ;
            }
        }
        const string path = "Musique/" + m.name + "&" + m.artist + ".mp3" ;
        const char *sout = "#transcode{acodec=mp3,ab=128,channels=2,samplerate=44100}:http{dst=:8090/m.mp3}";
        const char* media = "broadcast";

        lecteurMusique = libvlc_new(0, NULL);
        libvlc_vlm_add_broadcast(lecteurMusique, media, path.c_str(), sout, 0, NULL, true, false) ;
        libvlc_vlm_play_media(lecteurMusique, media) ;
    }
}

/**
 * Permet de stoper une musique et de la mettre en pause
 * @return true s'il y a une musique en streaming / false sinon ;
**/
bool Launcher::stopMusique(const ::Ice::Current&){
    if(lecteurMusique != NULL) {
        const char* media = "broadcast";

        libvlc_vlm_stop_media(lecteurMusique, media) ;
        libvlc_vlm_release(lecteurMusique) ;
        lecteurMusique = NULL ;

        return true;
    }

    return false;
}

/**
 * Permet d'afficher la liste totale de musique que le serveur connait
**/
void Launcher::display(const ::Ice::Current&){
    cout << "Voici la liste des titre disponible" << endl ;
    for(int i = 0 ; i < bdd_.size() ; i++) {
        Musique m = bdd_[i] ;
        cout << "id : " << m.id << "  " << m.name << "  " << m.artist << endl ;
    }
}

/**
 * Permet de retourner la liste de toutes les musiques au différents client qui pourront
 * la demander
**/
server::bdd Launcher::getBdd(const ::Ice::Current&) {
    return this->bdd_ ;
}