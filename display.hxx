#include <map>
#include <ncurses.h>
#include <vector>
#include <utility>
#include "filetype.hxx"
#include <map>
#include <filesystem>

#ifndef DISPLAY_HXX
#define DISPLAY_HXX

class Display {

    private:
        WINDOW* pad;
        int padHeight;
        const int backOptionLineNum = 2;
        const int printPathLineNum = 3;
        int padRowOffset = 0;
        //For the current path only. Resets the map only if current path is changed
        std::map<int, std::filesystem::path> mapLineNumToPath;
        std::filesystem::path matchPathByLineNum(int lineNum);


    public:
        //Only called when current path is changed
        void printDirectoryContents(std::vector<std::pair<Filetype, std::filesystem::path>> directoryContents, std::filesystem::path currentPath);
        void changeScreenState(int input);
        std::pair<int, int> getCurrentCursorPos();
        std::filesystem::path getPathChosen();
        bool isBackOptionChosen();
        void refreshPad();
        void erasePad();
        int listenForPadInput();

        Display();
        ~Display();
};

#endif
