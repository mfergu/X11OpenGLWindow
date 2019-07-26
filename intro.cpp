#include <X11/Xlib.h>
#include <iostream>

// XOpenDisplay(char* display)
//    makes connection to X server
//    returns a pointer to the display

// DefaultScreenOfDisplay(Display* display)
//    takes the pointer from XOpenDisplay
//    returns a pointer of type Screen on success

// DefaultScreen(Display* display)
//    same as DefaultScreenOfDisplay except
//    returns id of default screen as an int

// with just a display and a screen a window can be created with the XCreateSimpleWindow function

int main(int argc, char** argv){

   Display* display;
   Window window;
   Screen* screen;
   int screen_id;
   XEvent ev;

   std::cout << " creating a simple window " << std::endl;

   display = XOpenDisplay(NULL);
   if(display == NULL) {
      std::cout << " could not open display" << std::endl;
   }
   screen = DefaultScreenOfDisplay(display);
   screen_id = DefaultScreen(display);
   DefaultScreenOfDisplay(display);

   std::cout << " screen id: " << screen_id << std::endl;
   
   //Open the window
   window = XCreateSimpleWindow(display,
                                  RootWindowOfScreen(screen),
                                  0, 0, 320, 200, 1,
                                  BlackPixel(display, screen_id),
                                  WhitePixel(display, screen_id));

   //Show the window
   XClearWindow(display, window);
   XMapRaised(display, window);

   //enter message loop
   while (true) {
      XNextEvent(display, &ev);
      // do something
   }

   //cleanup
   XDestroyWindow(display, window);
   XFree(screen);
   XCloseDisplay(display);
   return 1;
}
