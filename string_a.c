#include "shell.h"

/**
 * _strcpy - Copies a string
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
int i = 0;

if (dest == src || src == NULL)
return (dest);

while (src[i])
{
dest[i] = src[i];
i++;
}

dest[i] = '\0';
return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string or NULL on failure
 */
char *_strdup(const char *str)
{
if (str == NULL)
return (NULL);

int length = 0;
while (str[length])
length++;

char *ret = malloc(sizeof(char) * (length + 1));
if (ret == NULL)
return (NULL);

for (int i = 0; i <= length; i++)
ret[i] = str[i];

return (ret);
}

/**
 * _puts - Prints a string to stdout
 * @str: The string to be printed
 */
void _puts(const char *str)
{
if (str == NULL)
return;

for (int i = 0; str[i]; i++)
_putchar(str[i]);
}

/**
 * _putchar - Writes a character to stdout
 * @c: The character to print
 *
 * Return: On success, 1. On error, -1 is returned.
 */
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;

return (1);
}
