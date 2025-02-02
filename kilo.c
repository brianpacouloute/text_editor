#include <termios.h>
#include <unistd.h>

void enableRawMode() {
    struct termios raw; /*storing file descriptor into Termios_p a pointed to struct termios holding terminal settings*/
    tcgetattr(STDIN_FILENO,&raw); /*sets value to struct*/
    raw.c_lflag &= ~(ECHO); /*This flag dictates if you can see your input in the temrinal*/
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw); /*Flush waits for all input to be written and extra input to be flushed before applying changes*/
}

int main() {
    enableRawMode();
    char c; /*Stored entered character*/
    while (read(STDIN_FILENO,&c,1) == 1 && c != 'q'); 
    return 0;
}