#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(bool enableGraphics, int width, int height) : enableGraphics{enableGraphics} {
    if (enableGraphics) {
        d = XOpenDisplay(NULL);
        if (d == NULL) {
            cerr << "Cannot open display" << endl;
            exit(1);
        }
        s = DefaultScreen(d);
        w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                                BlackPixel(d, s), WhitePixel(d, s));
        XSelectInput(d, w, ExposureMask | KeyPressMask);
        XMapRaised(d, w);

        Pixmap pix = XCreatePixmap(d,w,width,
                height,DefaultDepth(d,DefaultScreen(d)));
        gc = XCreateGC(d, pix, 0,(XGCValues *)0);

        XFlush(d);
        XFlush(d);

        // Set up colours.
        XColor xcolour;
        Colormap cmap;
        char color_vals[5][10]={"white", "black", "red", "green", "blue"};

        cmap=DefaultColormap(d,DefaultScreen(d));
        for(int i=0; i < 5; ++i) {
            XParseColor(d,cmap,color_vals[i],&xcolour);
            XAllocColor(d,cmap,&xcolour);
            colours[i]=xcolour.pixel;
        }

        XSetForeground(d,gc,colours[Black]);

        // Make window non-resizeable.
        XSizeHints hints;
        hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
        hints.height = hints.base_height = hints.min_height = hints.max_height = height;
        hints.width = hints.base_width = hints.min_width = hints.max_width = width;
        XSetNormalHints(d, w, &hints);

        XSynchronize(d,True);

        usleep(1000);
    }
}

Xwindow::~Xwindow() {
    if (enableGraphics) {
        XFreeGC(d, gc);
        XCloseDisplay(d);
    }
}

void Xwindow::clearArea(int x, int y, int width, int height) {
    XClearArea(d, w, x, y, width, height, true);
}

void Xwindow::clearHand() {
    clearArea(0, 0, boardWidth, cardHeight);
    y = yHand; 
}

void Xwindow::clearBoard() {
    clearArea(0, cardHeight, boardWidth, boardHeight);
    y = yBoard; 
}

void Xwindow::drawString(string msg) {
    XDrawString(d, w, DefaultGC(d, s), xPadding, y += stringHeight, msg.c_str(), msg.length());
}
