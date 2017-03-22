#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>

int main(int argc, char** argv, char** env)
{
    // Open a connection with the X server
    Display* Disp = XOpenDisplay(NULL);
    if (!Disp)
        return EXIT_FAILURE;

    // Get the default screen
    int Screen = DefaultScreen(Disp);

    // Let's create the main window
    XSetWindowAttributes Attributes;
    Attributes.background_pixel = WhitePixel(Disp, Screen);
    Attributes.event_mask       = KeyPressMask;
    Window Win = XCreateWindow(Disp, RootWindow(Disp, Screen),
                               0, 0, 650, 330, 0,
                               DefaultDepth(Disp, Screen),
                               InputOutput,
                               DefaultVisual(Disp, Screen),
                               CWBackPixel | CWEventMask, &Attributes);
    if (!Win)
        return EXIT_FAILURE;

    // Set the window's name
    XStoreName(Disp, Win, "SFML Window");

    // Let's create the window which will serve as a container for our SFML view
    Window View = XCreateWindow(Disp, Win,
                                10, 10, 310, 310, 0,
                                DefaultDepth(Disp, Screen),
                                InputOutput,
                                DefaultVisual(Disp, Screen),
                                0, NULL);

    // Show our windows
    XMapWindow(Disp, Win);
    XMapWindow(Disp, View);
    sf::RenderWindow SFMLView(View);
    XFlush(Disp);
    bool IsRunning = true;
    while (IsRunning)
    {
        while (XPending(Disp))
        {
            // Process the next pending event
            XEvent Event;
            XNextEvent(Disp, &Event);
            switch (Event.type)
            {
                case KeyPress :
                    IsRunning = false;
                    break;
            }
        }
        // Clear the view
        SFMLView.clear(sf::Color(255, 0, 0));
    }
    // Close the display
    XCloseDisplay(Disp);

    return 0;
}
