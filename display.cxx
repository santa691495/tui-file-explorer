#include "display.hxx"
#include "filesystemtypes.hxx"
#include <map>
#include <ncurses.h>
#include <string>
#include <utility>
#include <filesystem>

Display::Display()
{
    pad = newpad(500, 200);
    keypad(pad, TRUE);
}

Display::~Display()
{
    delwin(pad);
}

void Display::printDirectoryContents(FilesystemTypes::DirContents dirContents, std::filesystem::path currentPath)
{
    //* put this in its own function in Display, for explicity
    padRowOffset = 0;

    std::string titleStr = "<-[" + (std::string)currentPath + "]->";
    std::string backOptionStr = "[BACK]";
    std::string pathOptionsStr = "";

    for(FilesystemTypes::Entry entry: dirContents.getContents())
    {
        std::string filename = entry.getPathFileNameAsStr();

        FilesystemTypes::Filetype type = entry.getFileType();
        if(type == FilesystemTypes::Filetype::DIR)
        {
            pathOptionsStr.append("[DIR]").append(filename).append("\n");
        } else if(type == FilesystemTypes::Filetype::REGULAR_FILE)
        {
            pathOptionsStr.append("[FILE]").append(filename).append("\n");
        }
    }


    //print the title, backoption, and path options to their
    //designated lines
    wmove(pad, titleLineNum, 0);
    wprintw(pad, "%s", titleStr.c_str());

    wmove(pad, backOptionLineNum, 0);
    wprintw(pad, "%s", backOptionStr.c_str());

    wmove(pad, pathOptionsLineNumStart, 0);
    wprintw(pad, "%s", pathOptionsStr.c_str());

    //Put cursor on starting position after printing
    wmove(pad, cursorStartingLineNum, 0);
}

void Display::changeScreenState(int input, std::map<int, std::filesystem::path> lineNumToPathMapping)
{
    int maxY;
    int maxX;

    getmaxyx(stdscr, maxY, maxX);
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    switch (input)
    {
        //* provide brief explanation for these
        case KEY_UP:
            if(cursorPos.first > backOptionLineNum)
            {
                wmove(pad, cursorPos.first - 1, cursorPos.second);
                if(cursorPos.first - 1 < padRowOffset)
                {
                    padRowOffset--;
                }
            }
            break;
        //* provide brief explanation for these
        case KEY_DOWN:
            if(cursorPos.first < backOptionLineNum + lineNumToPathMapping.size())
            {
                wmove(pad, cursorPos.first + 1, cursorPos.second);
                if(cursorPos.first + 1 > padRowOffset + maxY - 1)
                {
                    padRowOffset++;
                }
            }
            break;
    }
}

std::pair<int, int> Display::getCurrentCursorPos()
{
    int currentY;
    int currentX;
    getyx(pad, currentY, currentX);
    return std::pair<int, int>(currentY, currentX);
}

void Display::refreshPad()
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    prefresh(pad, padRowOffset, 0, 0, 0, maxY - 1, maxX - 1);
}

void Display::erasePad()
{
    werase(pad);
}
