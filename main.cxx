#include "filesystem.hxx"
#include "display.hxx"
#include <ncurses.h>
#include <stdio.h>

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

    if(!fsystem.setCurrentPath(argv[1]))
    {
        clear();
        endwin();
        printf("Cannot access directory '%s'. No such directory.\n", argv[1]);
        return -1;
    }

    //print initial
    display.printDirectoryContents(
        fsystem.readCurrentPathContents(),
        fsystem.getCurrentPath()
    );
    display.refreshPad();

    while(true)
    {
        int input = display.listenForPadInput();

        //check if '[BACK]' or a specific directory was chosen and refresh
        //with new directory
        if(input == KEY_ENTER ||input == KEY_RIGHT ||input == 10)
        {

            if(display.isBackOptionChosen())
            {
                fsystem.setCurrentPathToParent();
            } else
            {
                fsystem.setCurrentPath(display.getPathChosen());
            }

            display.erasePad();
            display.printDirectoryContents(
                fsystem.readCurrentPathContents(),
                fsystem.getCurrentPath()
            );
        }

        //*should probably move the refresh action here, within its own function
        display.changeScreenState(input);
        display.refreshPad();
    }

    clear();
    endwin();

    return 0;
}
