/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                     //
//                                                                                                     //
//                                                                                                     //
//                                                                           _        ___  ____        //
//                                                 _ __ ___  _ __ ___   __ _(_)_ __  / _ \/ ___|       //
//   main.cpp                                      | '__/ _ \| '_ ` _ \ / _` | | '_ \| | | \___ \      //
//                                                 | | | (_) | | | | | | (_| | | | | | |_| |___) |     //
//   by: romainOS <contact.mromain@gmail.com>      |_|  \___/|_| |_| |_|\__,_|_|_| |_|\___/|____/      //
//                                                                                                     //
//   Created: 2019/05/23 00:22:35 by romainOS                                                          //
//   Updated: 2019/05/23 00:22:35 by romainOS                                                          //
//                                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

void add(std::string file, std::string prm) {
    std::ofstream monFlux(file, std::ios::out);

    if(monFlux) {
        monFlux << prm << std::endl;
    }
    else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

void del(std::string file, int ln) {
    std::string Buffer = ""; //Variable contenant le texte à réécrire dans le fichier
    std::ifstream ReadFile(file);
    if (ReadFile) { //Si le fichier est trouvé
        std::string line;
        int Line = 0;
        while(std::getline(ReadFile, line)) { //on parcours le fichier et on initialise line à la ligne actuelle
            Line++;
            if(Line != ln) //Si la ligne atteinte est différente de la ligne à supprimer...
                Buffer += line + "\n"; //On ajoute le contenu de la ligne dans le contenu à réécrire
        }
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
 
    std::ofstream WriteFile(file); //On ouvre ce même fichier en écriture
    WriteFile << Buffer; //On écris le texte dedans
}
void ls(std::string file) {
    std::ifstream ReadFile(file);
    if(ReadFile) {
        std::string line;
        while(std::getline(ReadFile, line)) {
                std::cout << line << std::endl;  // on l'affiche
        }
    } else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

int main(int argc, const char *argv[]) {
    //Set global filepath var.
    std::string const fileName("./todo.txt");

    if(argc < 2) {
        std::cout << "Usage: todo <parameter>!" << std::endl;
        return -1;
    }
    if(std::string(argv[1]) == "todo" && std::string(argv[2]) == "-a") {
        add(fileName, argv[3]);
    }
    if(std::string(argv[1]) == "todo" && std::string(argv[2]) == "-d") {
        del(fileName, atoi(argv[3]));
    }
    if(std::string(argv[1]) == "todo" && std::string(argv[2]) == "-ls") {
        ls(fileName);
    }

    return 0;
}