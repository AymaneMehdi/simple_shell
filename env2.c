#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: String array containing environment variables.
 */
char **get_environ(info_t *info)
{
return (environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
if (!var)
return (0);

int success = unsetenv(var);
if (success == 0)
{
info->env_changed = 1;
}
return (success);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: 0 on success, -1 on error
 */
int _setenv(info_t *info, char *var, char *value)
{
if (!var || !value)
return (-1);

int success = setenv(var, value, 1);
if (success == 0)
{
info->env_changed = 1;
}
return (success);
}
