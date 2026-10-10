#include <map>
#include <ncurses.h>
#include "filesystemtypes.hxx"
#include <utility>
#include <map>
#include <filesystem>

#ifndef DISPLAY_HXX
#define DISPLAY_HXX

class Display {

    private:
        WINDOW* pad;
        const int backOptionLineNum = 2;
        const int printPathLineNum = 3;
        int padRowOffset = 0;

        //For the current path only. Resets the map only if current path is changed
        //* mapping should probably be handled by something else
        //* or not make the matching be dependent on printing
        //  (i.e. create mapping first then print, not the other way around)
        std::map<int, std::filesystem::path> mapLineNumToPath;
        std::filesystem::path matchPathByLineNum(int lineNum);


    public:
        //Only called when current path is changed
        //*should be in its own function along with the erase operation in changeScreenState
        void printDirectoryContents(FilesystemTypes::DirContents dirContents, std::filesystem::path currentPath);
        void changeScreenState(int input);
        std::pair<int, int> getCurrentCursorPos();
        std::filesystem::path getPathChosen();
        bool isBackOptionChosen();
        void refreshPad();
        void erasePad();

        //*Display shouldnt wait for input, only handle output
        int listenForPadInput();

        Display();
        ~Display();
};

#endif
