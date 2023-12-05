#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
    const int cardHeight = 140;
    const int boardWidth = 1100;
    const int boardHeight = 600;
    const int xPadding = 10;
    const int stringHeight = 10;
    const int yCurrHand = 10;
    const int yBelowCurrHand = 150;
    Display *d;
    Window w;
    bool enableGraphics;
    int s;
    int y;
    GC gc;
    unsigned long colours[10];

    public:
        Xwindow(bool enableGraphics, int width=1020, int height=730);  // Constructor; displays the window.
        ~Xwindow();                              // Destructor; destroys the window.

        enum {White=0, Black, Red, Green, Blue}; // Available colours.

        void clearArea(int x, int y, int width, int height); // Resets y position to current hand.

        void clearHandArea(); // Resets y position to under current hand.

        void clearAreaUnderHand();

        // Draws a string
        void drawString(std::string msg);
};

#endif