#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
//https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
struct termios original_terminal;

void disabledRawMode() {
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_terminal);
}

void enableRawMode() {
    /*First we store the original terminal settings in a variable to later restore.*/
    tcgetattr(STDIN_FILENO,&original_terminal); /*sets value to struct*/
    
    atexit(disabledRawMode); /*call a funciton when exit*/

    struct termios raw = original_terminal;
    raw.c_iflag &= ~(ICRNL | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); /*This flag dictates if you can see your input in the temrinal*/
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw); /*Flush waits for all input to be written and extra input to be flushed before applying changes*/
}

int main() {
    enableRawMode();
    char c; /*Stored entered character*/
    while (read(STDIN_FILENO,&c,1) == 1 && c != 'q') {
        if (iscntrl(c)) { /*Checking if char is a control char \n \r \t \b \0*/
            printf("%d\n",c);
        } else {
            printf("%d ('%c')\n",c,c); /*%d gives ASCII code %c gives letter*/
        }
    } 
    return 0;
}