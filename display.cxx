#include "display.hxx"
#include "filetype.hxx"
#include <map>
#include <ncurses.h>
#include <string>
#include <vector>
#include <utility>

void Display::printDirectoryContents(std::vector<std::pair<Filetype, std::string>> directoryContents, std::string currentPath)
{
    mapLineNumToPath.clear();
    std::string titleString = "<-[" + currentPath + "]->\n";
    mvprintw(0, 0, "%s", titleString.c_str());

    std::string contentsString = "";
    int i = 0;
    for(auto &entry : directoryContents)
    {
        if(entry.first == Filetype::DIR)
        {
            contentsString.append("[DIR] ").append(entry.second).append("\n");
        } else {
            contentsString.append("[FILE] ").append(entry.second).append("\n");
        }
        mapLineNumToPath.insert({printPathLineNum + i, entry.second});
        i++;
    }

    mvprintw(printPathLineNum, 0, "%s", contentsString.c_str());
    move(printPathLineNum, 0);
}

void Display::changeScreenState(int input)
{
    int currentX;
    int currentY;

    getyx(stdscr, currentY, currentX);
    switch (input)
    {
        case KEY_UP:
            if(currentY != printPathLineNum)
                move(currentY - 1, currentX);
            break;
        case KEY_DOWN:
            if(currentY != printPathLineNum + mapLineNumToPath.size() - 1)
                move(currentY + 1, currentX);
            break;
        case KEY_RIGHT:
        case KEY_ENTER:
        case 10:
            move(printPathLineNum, 0);
            break;
    }
}

std::string Display::getPathChosen()
{
    int currentY;
    int currentX;
    getyx(stdscr, currentY, currentX);
    std::string pathChosen = mapLineNumToPath.at(currentY);

    return pathChosen;
}
