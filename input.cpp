#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <iostream>

// Key{Press, Release}Mask and KeymapStateMask
//    when keys are pressed or released
//    KeymapStateMask is when the keymapping of the system changes
//    
//    these events are subscribed to by checking the XEvent object with the masks
//       there are many different masks
//          https://tronche.com/gui/x/xlib/events/processing-overview.html

// if KeyMapNotify event occurs call XRefreshKeyboardMapping(XMappingEvent* event_map)
//    it takes one argument XMappingEvent pointer

// if KeyPress or KeyRelease events fire call int XLookupString(XKeyEvent *event_struct,
//                                                              char* buffer_return,
//                                                              int bytes_buffer,
//                                                              KeySym* keysym_return,
//                                                              XComposeStatus* status_in_out);
//
//    this translates the event into a KeySym (a typedef for the key pressed) and a string.
//    buffer_return will hold the translated character string
//    keysym_return will hold the KeySym value
//    keysymdef.h is the list of #define strings for each key

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

   std::cout << " screen id: " << screen_id << std::endl;
   
   //Open the window
   window = XCreateSimpleWindow(display,
                                  RootWindowOfScreen(screen),
                                  0, 0, 320, 200, 1,
                                  BlackPixel(display, screen_id),
                                  WhitePixel(display, screen_id));

   XSelectInput(display, window, KeyPressMask | KeyReleaseMask | KeymapStateMask);

   //Show the window
   XClearWindow(display, window);
   XMapRaised(display, window);

   //variables used in message loop
   char str[25] = {0};
   KeySym keysym = 0;
   int len = 0;
   bool running = true;

   //enter message loop
   while (running) {
      XNextEvent(display, &ev);
      switch(ev.type) {
         case KeymapNotify:
            XRefreshKeyboardMapping(&ev.xmapping);
         break;
         case KeyPress:
            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
            if(len > 0) {
               std::cout << "key pressed: " << str << " - " << len << " - " <<
                                                          keysym << std::endl;
            }
            if (keysym == XK_Escape) {
               running = false;
            }
         break;
         case KeyRelease:
            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
            if(len > 0) {
               std::cout << "key pressed: " << str << " - " << len << " - " <<
                                                          keysym << std::endl;
            }
         break;
      }
   }

   //cleanup
   XDestroyWindow(display, window);
   XFree(screen);
   XCloseDisplay(display);
   return 1;
}



















