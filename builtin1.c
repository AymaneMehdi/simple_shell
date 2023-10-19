#include "shell.h"
#include <stdio.h>

/**
 * my_history - Display the history list with line numbers.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_history(info_t *info)
{
print_list(info->history);
return (0);
}

/**
 * unset_alias - Remove an alias from the list.
 * @info: Parameter structure.
 * @str: The string alias to remove.
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, const char *str)
{
char *p, c;
int ret;
p = _strchr((char *)str, '=');
if (!p)
return 1;
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - Add or update an alias in the list.
 * @info: Parameter structure.
 * @str: The string alias to add/update.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, const char *str)
{
char *p;
p = _strchr((char *)str, '=');
if (!p)
return 1;
if (!*++p)
return unset_alias(info, str);

unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * my_alias - Manage shell aliases.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_alias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}
