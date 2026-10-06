#include <map>
#include <string>
#include <ncurses.h>
#include <vector>
#include <utility>
#include "filetype.hxx"
#include <map>

#ifndef DISPLAY_HXX
#define DISPLAY_HXX

class Display {

    private:
        const int printPathLineNum = 2;
        //For the current path only. Resets the map only if current path is changed
        std::map<int, std::string> mapLineNumToPath;


    public:
        //Only called when current path is changed
        void printDirectoryContents(std::vector<std::pair<Filetype, std::string>> directoryContents, std::string currentPath);
        void changeScreenState(int input);
        std::string getPathChosen();
};

#endif
