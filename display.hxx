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
        const int pathOptionsLineNumStart = 3;
        const int titleLineNum = 0;
        const int cursorStartingLineNum = backOptionLineNum;
        int padRowOffset = 0;

    private:
        void resetPadRowOffset();
        void adjustScrollOffsetUp();
        void adjustScrollOffsetDown();
        bool canPadScrollOffsetDown();
        bool canPadScrollOffsetUp();
        bool canCursorMoveUp();
        bool canCursorMoveDown(std::map<int, std::filesystem::path> lineNumToPathMapping);

    public:
        void printDirectoryContents(FilesystemTypes::DirContents &dirContents, std::filesystem::path currentPath);
        std::pair<int, int> getCurrentCursorPos();
        void refreshPad();
        void erasePad();

        void moveCursorDown(int input, std::map<int, std::filesystem::path> lineNumToPathMapping);
        void moveCursorUp(int input);

        Display();
        ~Display();
};

#endif
