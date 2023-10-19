#include "shell.h"
/* rl : Read Line function */
 char *rl(void)
 {
    s_t len = 0;
    s_t1 n;
    /*Display a prompt and wait for the user to type a command*/
    if (isatty(STDIN_FILEND))
      write(STDOUT_FILENO, "$ ", 2);
    n = getline(&line, &len, stdin);

    if( n==-1)
    {
     /* free(line); */
        return (NULL);
    }

    return(line);
 }