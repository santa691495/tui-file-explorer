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

void Display::printDirectoryContents(FilesystemTypes::DirContents &dirContents, std::filesystem::path currentPath)
{

    resetPadRowOffset();

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

void Display::moveCursorDown(int input, std::map<int, std::filesystem::path> lineNumToPathMapping)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    //TODO: explain the math here in simple terms
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(canCursorMoveDown(lineNumToPathMapping))
    {
        wmove(pad, cursorPos.first + 1, cursorPos.second);
        adjustScrollOffsetDown();
    }
}

void Display::moveCursorUp(int input)
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    //TODO: explain the math here in simple terms
    if(canCursorMoveUp())
    {
        wmove(pad, cursorPos.first - 1, cursorPos.second);
        adjustScrollOffsetUp();
    }
}

void Display::resetPadRowOffset()
{
    padRowOffset = 0;
}

void Display::adjustScrollOffsetDown()
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(canPadScrollOffsetDown())
    {
        padRowOffset++;
    }
}

void Display::adjustScrollOffsetUp()
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(canPadScrollOffsetUp())
    {
        padRowOffset--;
    }
}

bool Display::canPadScrollOffsetDown()
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(cursorPos.first + 1 > padRowOffset + maxY - 1)
    {
        return true;
    }
    return false;
}

bool Display::canPadScrollOffsetUp()
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(cursorPos.first - 1 < padRowOffset)
    {
        return true;
    }
    return false;
}

bool Display::canCursorMoveDown(std::map<int, std::filesystem::path> lineNumToPathMapping)
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(cursorPos.first < backOptionLineNum + lineNumToPathMapping.size())
    {
       return true;
    }
    return false;
}

bool Display::canCursorMoveUp()
{
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    if(cursorPos.first > backOptionLineNum)
    {
        return true;
    }
    return false;
}
