#include "filesystem.hxx"
#include "display.hxx"
#include <ncurses.h>
#include <stdio.h>

int main (int argc, char* argv[])
{

    initscr();
    keypad(stdscr, TRUE);
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

    while(true)
    {
        int input = getch();

        if(input == KEY_ENTER ||input == KEY_RIGHT ||input == 10)
        {
            fsystem.setCurrentPath(display.getPathChosen());
            erase();
            display.printDirectoryContents(
                fsystem.readCurrentPathContents(),
                fsystem.getCurrentPath()
            );
            refresh();
        }

        display.changeScreenState(input);
        refresh();
    }

    clear();
    endwin();
    //get path contents
    // print to screen
    // wait for input
    // pass input to filesystem to change currentPath if
        //  new path is passed

    return 0;
}
