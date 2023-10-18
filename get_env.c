#include "shell.h"
#include <string.h> // Include necessary libraries
#include <stdlib.h> // Include necessary libraries for malloc

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: The Structure containing potential arguments.
 * Return: The array of environment variables.
 */
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}

return info->environ;
}

/**
 * my_unsetenv - Remove an environment variable.
 * @info: The Structure containing potential arguments.
 * @var: The string env var property.
 * Return: 1 on delete, 0 otherwise.
 */
int my_unsetenv(info_t *info, const char *var)
{
list_t *node = info->env;
size_t i = 0;

if (!node || !var)
return 0;

while (node)
{
char *p = starts_with(node->str, var);
if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return info->env_changed;
}

/**
 * my_setenv - Initialize a new environment variable or modify an existing one.
 * @info: The Structure containing potential arguments.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */
int my_setenv(info_t *info, const char *var, const char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return 0;

buf = malloc(strlen(var) + strlen(value) + 2);
if (!buf)
return 1;
strcpy(buf, var);
strcat(buf, "=");
strcat(buf, value);
node = info->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return 0;
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return 0;
}
