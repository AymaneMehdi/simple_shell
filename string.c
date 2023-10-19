#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string whose length is to be checked.
 *
 * Return: Integer length of the string.
 */
int _strlen(const char *s)
{
int length = 0;

if (!s)
return (0);

while (*s != '\0')
{
length++;
s++;
}

return (length);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(const char *s1, const char *s2)
{
while (*s1 != '\0' && *s2 != '\0')
{
if (*s1 != *s2)
return (*s1 - *s2);

s1++;
s2++;
}

return (*s1 - *s2);
}

/**
 * starts_with - Checks if a string starts with another string.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack or NULL.
 */
const char *starts_with(const char *haystack, const char *needle)
{
while (*needle != '\0')
{
if (*needle != *haystack)
return (NULL);

haystack++;
needle++;
}

return (haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
char *ret = dest;

while (*dest != '\0')
dest++;

while (*src != '\0')
{
*dest = *src;
dest++;
src++;
}

*dest = '\0';

return (ret);
}
