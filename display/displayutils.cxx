#include "displayutils.hxx"
#include "filesystemtypes.hxx"
#include <filesystem>
#include <map>
#include <ncurses.h>

const std::map<int, std::filesystem::path> DisplayUtils::generateLineNumToPathMapping(
    int lineNumStart, FilesystemTypes::DirContents dirContents
)
{
    int optionIndex = 0;
    std::map<int, std::filesystem::path> mapping;
    for(FilesystemTypes::Entry entry: dirContents.getContents())
    {
        mapping.insert({lineNumStart + optionIndex, entry.getPath()});
        ++optionIndex;
    }

    return mapping;
}


std::pair<int, int> DisplayUtils::getCurrentCursorPos(WINDOW* window)
{
    int currentY;
    int currentX;
    getyx(window, currentY, currentX);
    return std::pair<int, int>(currentY, currentX);
}
