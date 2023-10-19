#include "shell.h"
#include <string.h> /** Include the standard library for string functions */

/**
 * my_strncpy - Copy a string (up to n characters) from src to dest.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: The destination string.
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
return (strncpy(dest, src, n));
}

/**
 * my_strncat - Concatenate two strings (up to n characters) and store
 * the result in dest.
 * @dest: The destination string.
 * @src: The source string to concatenate.
 * @n: The maximum number of characters to concatenate.
 * Return: The destination string.
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
return (strncat(dest, src, n));
}

/**
 * my_strchr - Locate the first occurrence of a character in a string.
 * @s: The string to search in.
 * @c: The character to locate.
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL
 * if not found.
 */
char *my_strchr(const char *s, int c)
{
return (strchr(s, c));
}
