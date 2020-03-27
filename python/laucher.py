import sys, os, Ice

currentDir = os.path.join(os.path.dirname(__file__))
parrentDir = os.path.dirname(currentDir)
sys.path.insert(0, parrentDir)

import server

def init():
    global communicator
    global serveur 
    communicator = Ice.initialize(sys.argv)
    base = communicator.stringToProxy("Serveur:tcp -h 192.168.1.98 -p 10000")
    try:
        serveur = server.ServeurIcePrx.checkedCast(base)
    except:
        print("Vrou vr.... le serveur est eteint")
        communicator.destroy()
        exit()
    
    if not serveur:
        raise RuntimeError("Proxy invalide")

def ajouterMusique():
    print("Vous avez choisis d'ajouter une musique")
    print("Entrer le nom de la musique")
    name = raw_input("---> ")
    ok = serveur.ajouterMusique(name)
    
    if (ok):
        print("Ajouter")
    else:
        print("Refuser")

def jouerMusique():
    print("Vous avez choisis de jouer une musique")
    playlist = serveur.getBdd()
    if(len(playlist) > 0):
        print(str(playlist))
        print("Selectionner ")
        id = int(input("---> "))
        serveur.jouerMusique(id)

"""
def stopMusique():
    arret = server.stopMusique()
    if(arret):
        print("Arret de la musique")
    else:
        print("Pas de musique")
"""

def display():
    serveur.display()
    playlist = serveur.getBdd()
    print("Liste de musique \n"+str(playlist))

def menu(): 
    stop = False
    while not stop:
        print("Bienvenue, selectionner votre action")
        print("1 - ajouter une musique")
        print("2 - jouer une musique")
        print("3 - arreter une musique")
        print("4 - afficher la liste de musique")
        print("5 - exit")
        choix = str(input("--> "))
        
        if choix == "1":
            print("choix 1")
            ajouterMusique()
        elif choix == "2":
            jouerMusique()
        elif choix == "3":
            stopMusique()
        elif choix == "4":
            display()
        elif choix == "5":
            sys.exit(0)


init()
menu()