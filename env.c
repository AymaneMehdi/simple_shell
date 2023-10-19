#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
char **env_ptr = environ;
while (*env_ptr != NULL)
{
_puts(*env_ptr);
_putchar('\n');
env_ptr++;
}
return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
char **env_ptr = environ;
while (*env_ptr != NULL)
{
if (_strncmp(*env_ptr, name, _strlen(name)) == 0)
{
char *value = *env_ptr + _strlen(name) + 1;
return (value);
}
env_ptr++;
}
return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}

char *name = info->argv[1];
char *value = info->argv[2];

int success = setenv(name, value, 1);
if (success == -1)
{
perror("Error setting environment variable");
return (1);
}

return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
int i;
for (i = 1; i < info->argc; i++)
{
int success = unsetenv(info->argv[i]);
if (success == -1)
{
perror("Error unsetting environment variable");
return (1);
}
}
return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
    /** No need to populate, environ is already populated. */
/** The environment variables are stored in the global variable `environ` */
/** `environ` is an array of strings where each string has the format "NAME=VALUE".*/
info->env = NULL; /**Set to NULL since we are not using a linked list.*/
return (0);
}
