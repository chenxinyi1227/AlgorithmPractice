#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep() function
#include <ncurses.h>

int main()
{
#if 0
    initscr(); // initialize the screen
    
    printw("Hello World"); // print string to terminal
    
    refresh(); // update display content
    
    getch(); // wait for user input before exiting program
    
    endwin(); // clean up and restore terminal settings

#else
    initscr();
    printw("Hello World !!!");
    refresh();
    getch();
    endwin();
    return 0;

#endif
    return 0;
}
