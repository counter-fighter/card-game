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
  const int yCurrHand = 20;
  const int yBelowCurrHand = 170;
  Display *d;
  Window w;
  int s;
  int y;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=1020, int height=730);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  int getX() const;

  int getY() const;

  int yNextLine();

  void clearArea(int x, int y, int width, int height);

  void clearHandArea();

  void clearAreaUnderHand();

  // Draws a string
  void drawString(int x, int y, std::string msg);
};

#endif
