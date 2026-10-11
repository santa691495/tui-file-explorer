#include <ncurses.h>
#include "input.hxx"

int Input::listenForPadInput(WINDOW* pad)
{
    int input = wgetch(pad);
    return input;
}
