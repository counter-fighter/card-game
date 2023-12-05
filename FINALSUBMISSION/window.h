#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
    Display *d;
    Window w;
    bool enableGraphics;
    int s;
    GC gc;
    unsigned long colours[10];

    // Constants and variable specially for printing cards
    const int cardHeight = 140;
    const int boardWidth = 1100;
    const int boardHeight = 600;
    const int xPadding = 10;
    const int stringHeight = 10;
    const int yHand = 10;
    const int yBoard = 150;
    int y;

    public:
        // Displays the window with dimensions large enough to display both a hand and board. If 
        //   enableGraphics is false, nothing happens.
        Xwindow(bool enableGraphics, int width=1020, int height=730); 
        
        // Destroys the window. If enableGraphics is false, nothing happens.
        ~Xwindow(); 

        enum {White=0, Black, Red, Green, Blue}; // Available colours.

        // Clears area on window at x and y, with specified width and height.
        void clearArea(int x, int y, int width, int height); // 

        // Clears area where hand is displayed on window. y is resetted to yHand.
        void clearHand(); 

        // Clears area where board is displayed on window. y is resetted to yBoard.
        void clearBoard();

        // Draws a string and increments y by stringHeight.
        void drawString(std::string msg);
};

#endif