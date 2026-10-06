#include "display.hxx"
#include "filetype.hxx"
#include <map>
#include <ncurses.h>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>

void Display::printDirectoryContents(std::vector<std::pair<Filetype, std::filesystem::path>> directoryContents, std::filesystem::path currentPath)
{
    mapLineNumToPath.clear();
    std::string titleString = "<-[" + (std::string)currentPath + "]->\n";
    mvprintw(0, 0, "%s", titleString.c_str());

    std::string contentsString = "[BACK]\n";
    int i = 0;
    for(auto &entry : directoryContents)
    {
        if(entry.first == Filetype::DIR)
        {
            contentsString.append("[DIR] ").append((std::string)entry.second).append("\n");
        } else
        {
            contentsString.append("[FILE] ").append((std::string)entry.second).append("\n");
        }
        mapLineNumToPath.insert({printPathLineNum + i, entry.second});
        i++;
    }

    mvprintw(backOptionLineNum, 0, "%s", contentsString.c_str());
    move(backOptionLineNum, 0);
}

void Display::changeScreenState(int input)
{
    int currentX;
    int currentY;

    getyx(stdscr, currentY, currentX);
    switch (input)
    {
        case KEY_UP:
            if(currentY != backOptionLineNum)
                move(currentY - 1, currentX);
            break;
        case KEY_DOWN:
            if(currentY != backOptionLineNum + mapLineNumToPath.size())
                move(currentY + 1, currentX);
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
    getyx(stdscr, currentY, currentX);
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
