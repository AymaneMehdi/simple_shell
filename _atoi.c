#include "shell.h"
#include <ctype.h> // for isdigit function

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: pointer to info_t structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to be checked
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, const char *delim)
{
while (*delim)
{
if (*delim++ == c)
return 1;
}
return 0;
}

/**
 * is_alpha - checks for an alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
return isalpha(c);
}

/**
 * atoi_custom - converts a string to an integer
 * @s: the string to be converted
 * Return: the converted integer, or 0 if no numbers are found
 */
int atoi_custom(const char *s)
{
int sign = 1;
unsigned int result = 0;
    
if (*s == '-')
{
sign = -1;
s++;
}   
while (*s)
{
if (isdigit(*s))
{
result = result * 10 + (*s - '0');
}
else
{
/** Handle non-digit characters */
}
s++;
}
return (sign * result);
}
