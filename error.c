#include "shell.h"
#include <unistd.h> /** Include necessary libraries */

/**
 * _eputs - Print an input string to stderr.
 * @str: The string to be printed.
 */
void _eputs(const char *str)
{
if (str)
{
write(STDERR_FILENO, str, _strlen(str));
}
}

/**
 * _eputchar - Write a character to stderr.
 * @c: The character to print.
 * Return: On success 1.
 * On error, -1 is returned, and error is correctly set.
 */
int _eputchar(char c)
{
return (write(STDERR_FILENO, &c, 1));
}

/**
 * _putfd - Write a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success 1.
 * On error, -1 is returned, and error is set correctly.
 */
int _putfd(char c, int fd)
{
return (write(fd, &c, 1));
}

/**
 * _putsfd - Print an input string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 */
int _putsfd(const char *str, int fd)
{
int count = 0;
    
if (str)
{
count = write(fd, str, _strlen(str));
}
return (count);
}
