#include <ncurses.h>

#ifndef INPUT_HXX
#define INPUT_HXX

class Input {
    public:
        int listenForPadInput(WINDOW* pad);
};

#endif
