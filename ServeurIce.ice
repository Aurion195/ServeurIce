module server {
    struct Musique {
        int id;
        string name;
        string artist;
    };

    sequence<Musique> bdd;

    interface ServeurIce {
        bool ajouterMusique(string name) ;
        void jouerMusique(int id) ;
        bool stopMusique() ;
        void display();
        bdd getBdd();
    };
};