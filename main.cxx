#include "filesystem.hxx"
#include "filesystemtypes.hxx"
#include "filesystemutils.hxx"
#include "input.hxx"
#include "eventlistener.hxx"
#include "displaytypes.hxx"
#include "displayutils.hxx"
#include "display.hxx"
#include <ncurses.h>
#include <stdio.h>
//TODO:
int main (int argc, char* argv[])
{

    initscr();
    noecho();

    if(argc > 2)
    {
        clear();
        endwin();
        printf("Too many arguments. Usage: file-mgr <path>\n");
        return -1;
    } else if(argc == 1){
        clear();
        endwin();
        printf("Usage: file-mgr <path>\n");
        return -1;
    }

    Filesystem fsystem;
    Display display;
    Input inputListener;
    EventListener eventListener;

    //use FilesystemUtils::isDirValid()
    if(!fsystem.setCurrentPath(argv[1]))
    {
        clear();
        endwin();
        printf("Cannot access directory '%s'. No such directory.\n", argv[1]);
        return -1;
    }

    //print initial
    FilesystemTypes::DirContents initDirContents = FilesystemUtils::generateDirContentsFromPath(fsystem.getCurrentPath());
    display.printDirectoryContents(initDirContents, fsystem.getCurrentPath());
    display.refreshPad();

    eventListener.mapKeyToEvent(KEY_UP, [&]()-> void {
        display.moveCursorUp();
        display.refreshPad();
    });

    eventListener.mapKeyToEvent(KEY_DOWN, [&]()-> void {
        FilesystemTypes::DirContents currentDirContents = FilesystemUtils::generateDirContentsFromPath(fsystem.getCurrentPath());
        display.moveCursorDown(currentDirContents);
        display.refreshPad();
    });

    eventListener.mapKeyToEvent(KEY_RIGHT, [&]()-> void {
        if(display.isCursorAtOptionType(DisplayTypes::Options::BACK))
        {
            fsystem.setCurrentPathToParent();
        } else if(display.isCursorAtOptionType(DisplayTypes::Options::PATH))
        {
            //*Retrieve the chosen path by getting the line where the cursor was last pointing at
            //during KEY_RIGHT press event, after generating a line-number-to-filepath map.

            FilesystemTypes::DirContents currentDirContents = FilesystemUtils::generateDirContentsFromPath(fsystem.getCurrentPath());
            int startLineNum = display.getStartLineNumForOptionType(DisplayTypes::Options::PATH);

            std::map<int, std::filesystem::path> lineNumToPathMapping = DisplayUtils::generateLineNumToPathMapping(
                startLineNum, currentDirContents
            );

            std::pair<int, int> lastCursorPos = DisplayUtils::getCurrentCursorPos(display.getPad());
            std::filesystem::path pathChosen = lineNumToPathMapping.at(lastCursorPos.first);

            fsystem.setCurrentPath(pathChosen);
        }

        FilesystemTypes::DirContents newDirContents = FilesystemUtils::generateDirContentsFromPath(fsystem.getCurrentPath());
        display.erasePad();
        display.printDirectoryContents(newDirContents, fsystem.getCurrentPath());
        display.refreshPad();
    });

    while(true)
    {
        int input = inputListener.listenForPadInput(display.getPad());
        eventListener.registerForInput(input);
    }

    clear();
    endwin();

    return 0;
}
