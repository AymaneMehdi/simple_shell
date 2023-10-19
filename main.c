* @a : count of argumnents
* @av : argumnents
* return : 0 always whene success
int main(int a, char **av)
{
    char *line = null;
    **cammand = NULL;
    int status = 0;
    (void) ac;
    (void) av;

    while (1)
    {
        line = rl();
        
        if (line == NULL)/* reache EOF ctr + D */
        {
            if (isatty(STDIN_FILEND))
            /*A command line always ends with a new line*/
            write(STDOUT_FILENO, "\n", 1);
            return (status);
        }
        
        

        printf("%s",line);
        
        cammand = tokenizer(line);

        status = _execute(cammand,av);
    }

}