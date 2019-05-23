/* *************************************************************************************************** */
/*                                                                                                     */
/*                                                                                                     */
/*                                                                                                     */
/*                                                                           _        ___  ____        */
/*                                                 _ __ ___  _ __ ___   __ _(_)_ __  / _ \/ ___|       */
/*   main.cpp                                      | '__/ _ \| '_ ` _ \ / _` | | '_ \| | | \___ \      */
/*                                                 | | | (_) | | | | | | (_| | | | | | |_| |___) |     */
/*   by: romainOS <contact.mromain@gmail.com>      |_|  \___/|_| |_| |_|\__,_|_|_| |_|\___/|____/      */
/*                                                                                                     */
/*   Created: 2019/05/23 00:22:35 by romainOS                                                          */
/*   Updated: 2019/05/23 00:22:35 by romainOS                                                          */
/*                                                                                                     */
/* *************************************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>

std::vector<std::string> readSentence(int argc, char * argv[]){
    std::vector<std::string> tab;
    for(int i=3; i<argc;++i){
        tab.emplace_back(argv[i]);
    }
    return tab;
}
/* on recrée la phrase, sur base de chaque mot */
std::string createSentence(std::vector<std::string> const & words){
    size_t count(0);
    std::string sentence;
    for(auto const & it : words){
        sentence+= it;
        ++count;
        if(count <words.size())
             sentence+=" ";
    }
    return sentence;
}
/* Par facilité, on pourrait créer une énumération permettant de représenter les instruction */
enum Instructions{
    addToText,
    list,
    delFromText,
    MAXINSTRUCTIONS
};
/* Grâce à elle, nous pouvons analyser l'instruction qui est donnée sous une forme proche de */
Instructions selectInstruction(std::string const & str){
    if(str == "-a")
        return Instructions::addToText;
    if(str=="-d")
       return Instructions::delFromText;
    if(str=="-ls")
      return Instructions::list;
    return Instructions::MAXINSTRUCTIONS;
}

int extractLineNumber(std::string const & str){
	size_t position(0);
	int result = std::stoi(str, &position);
	if(position!= str.size())
		throw std::runtime_error("unable to extract line numbeer from command line");
	return result;
}

/* on s'assure que le premier paramètre est "todo" */
void checkFirstArg(std::string const & str){
     if(str!="todo")
        throw std::runtime_error("first argument should be ''todo''");
}

void add(std::string file, std::string prm) {
    std::ofstream monFlux(file, std::ios::app);
 
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

void less(std::string file) {
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

int main(int argc, char * argv[]){
    if(argc <3)
        throw std::runtime_error("Usage: todo <instruction> <paramètres éventuels>!");
    checkFirstArg(argv[1]);
    auto instr = selectInstruction(argv[2]);
    std::string const fileName("./todo.txt");
    /* récupération de la phrase (s'il y en a une)
     * parce que le compilateur n'aime pas trop que l'on déclare une variable dans les switch ;) 
     */
   auto words = readSentence(argc, argv);
   auto recup = createSentence(words);
    switch(instr){
        case addToText:
            /* on récupère les mots */
            add(fileName, recup);
           break;
        case list :
            less(fileName);
           break;
        case delFromText:
	    del(fileName, extractLineNumber(argv[3]));
	   break;
        default:
            assert(false && "you should never come here");
    }
    /* ... */
    return 0;
}
