#include "shell.h"

/**
 * **strtow - Splits a string into words using multiple delimiters.
 * @str: The input string.
 * @delimiters: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *delimiters)
{
int i, j, k, m, numwords = 0;
char **words;

if (str == NULL || str[0] == '\0')
return (NULL);

if (!delimiters)
delimiters = " ";

/** Count the number of words */
for (i = 0; str[i] != '\0'; i++)
{
if (!is_delimiter(str[i], delimiters) && (is_delimiter(str[i + 1], delimiters)
|| str[i + 1] == '\0'))
numwords++;
}

if (numwords == 0)
return (NULL);

words = malloc((numwords + 1) * sizeof(char *));
if (!words)
return (NULL);

for (i = 0, j = 0; j < numwords; j++)
{
while (is_delimiter(str[i], delimiters))
i++;

k = 0;
while (!is_delimiter(str[i + k], delimiters) && str[i + k] != '\0')
k++;

words[j] = malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}

for (m = 0; m < k; m++)
words[j][m] = str[i++];

words[j][m] = '\0';
}

words[j] = NULL;
return (words);
}

/**
 * **strtow2 - Splits a string into words using a single delimiter.
 * @str: The input string.
 * @delimiter: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char delimiter)
{
int i, j, k, m, numwords = 0;
char **words;

if (str == NULL || str[0] == '\0')
return (NULL);

/** Count the number of words */
for (i = 0; str[i] != '\0'; i++)
{
if ((str[i] != delimiter && str[i + 1] == delimiter) ||
(str[i] != delimiter && str[i + 1] == '\0') ||
str[i + 1] == delimiter)
{
numwords++;
}
}

if (numwords == 0)
return (NULL);

words = malloc((numwords + 1) * sizeof(char *));
if (!words)
return (NULL);

for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == delimiter && str[i] != '\0')
i++;

k = 0;
while (str[i + k] != delimiter && str[i + k] != '\0')
k++;

words[j] = malloc((k + 1) * sizeof(char));
if (!words[j])
{
for (k = 0; k < j; k++)
free(words[k]);
free(words);
return (NULL);
}

for (m = 0; m < k; m++)
words[j][m] = str[i++];

words[j][m] = '\0';
}

words[j] = NULL;
return (words);
}
