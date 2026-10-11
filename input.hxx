#include <ncurses.h>

#ifndef INPUT_HXX
#define INPUT_HXX

class Input {
    private:
        int recentInput;

    public:
        int listenForPadInput(WINDOW* pad);
        int getRecentInput();
};

#endif
