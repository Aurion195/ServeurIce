#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <launcher.h>

using namespace std;
using namespace server;

int launcher::cpt = 0 ;

launcher::launcher(int size) {
    this->bdd_.resize(size) ;
}

launcher::~launcher() {

}

void launcher::ajout(Musique m) {
    m.id = cpt++;
    bdd_.push_back(m) ;
}

bool launcher::ajouterMusique(string name, const ::Ice::Current&) {
    const string nameFile = "Musique/" + name ;
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

void launcher::jouerMusique(int id, const ::Ice::Current&) {
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

    vlc = libvlc_new(0, NULL);
    cout << path << endl ;
    libvlc_vlm_add_broadcast(vlc, media, path.c_str(), sout, 0, NULL, true, false) ;
    libvlc_vlm_play_media(vlc, media) ;
}

void launcher::display(const ::Ice::Current&){
    cout << "Voici la liste des titre disponible" << endl ;
    for(int i = 0 ; i < bdd_.size() ; i++) {
        Musique m = bdd_[i] ;
        cout << "id : " << m.id << "  " << m.name << "  " << m.artist << endl ;
    }
}

server::bdd launcher::getBdd(const ::Ice::Current&) {
    return this->bdd_ ;
}