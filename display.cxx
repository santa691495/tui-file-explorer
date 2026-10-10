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

//FIX
void Display::printDirectoryContents(FilesystemTypes::DirContents dirContents, std::filesystem::path currentPath)
{
    padRowOffset = 0;
    mapLineNumToPath.clear();

    //* one accidental newline will break the entire tracking,
    //redesign the tracking system (better) or create an explicit way
    //to track the spacing.
    std::string title = "<-[" + (std::string)currentPath + "]->\n\n";
    std::string options = "[BACK]\n";

    //*The printing must be determined by mapLineNumToPath, not
    //printing it first then map it; this makes it dependent on the
    //printing which is unreliable.
    int i = 0;
    for(FilesystemTypes::Entry entry: dirContents.getContents())
    {
        std::string filename = entry.getPathFileNameAsStr();

        FilesystemTypes::Filetype type = entry.getFileType();
        if(type == FilesystemTypes::Filetype::DIR)
        {
            options.append("[DIR]").append(filename).append("\n");
        } else if(type == FilesystemTypes::Filetype::REGULAR_FILE)
        {
            options.append("[FILE]").append(filename).append("\n");
        }
        //* unreliable
        mapLineNumToPath.insert({printPathLineNum + i, entry.getPath()});
        i++;
    }

    std::string full = title + options;

    wprintw(pad, "%s", full.c_str());
    wmove(pad, backOptionLineNum, 0);
}

void Display::changeScreenState(int input)
{
    int maxY;
    int maxX;

    getmaxyx(stdscr, maxY, maxX);
    std::pair<int, int> cursorPos = getCurrentCursorPos();
    switch (input)
    {
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
        case KEY_DOWN:
            if(cursorPos.first < backOptionLineNum + mapLineNumToPath.size())
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

std::filesystem::path Display::matchPathByLineNum(int lineNum)
{
    return mapLineNumToPath.at(lineNum);
}

std::pair<int, int> Display::getCurrentCursorPos()
{
    int currentY;
    int currentX;
    getyx(pad, currentY, currentX);
    return std::pair<int, int>(currentY, currentX);
}

std::filesystem::path Display::getPathChosen()
{
    return matchPathByLineNum(getCurrentCursorPos().first);
}

bool Display::isBackOptionChosen()
{
    if(getCurrentCursorPos().first == backOptionLineNum)
    {
        return true;
    }
    return false;
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

int Display::listenForPadInput()
{
    int input = wgetch(pad);
    return input;
}
