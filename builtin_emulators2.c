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
char *equal_sign = _strchr((char *)str, '=');

if (equal_sign)
{
*equal_sign = '\0'; /**Null terminate the string at the position of '='*/
int result = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*equal_sign = '='; /**Restore the original string*/
return (result);
}
return (1);
}

/**
 * set_alias - Add or update an alias in the list.
 * @info: Parameter structure.
 * @str: The string alias to add/update.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, const char *str)
{
char *equal_sign = _strchr((char *)str, '=');

if (equal_sign)
{
*equal_sign = '\0'; /**Null terminate the string at the position of '='*/
unset_alias(info, str);
*equal_sign = '=';
return (add_node_end(&(info->alias), str, 0) == NULL);
}
return (1);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
if (node)
{
char *equal_sign = _strchr(node->str, '=');
if (equal_sign)
{
for (char *a = node->str; a <= equal_sign; a++)
_putchar(*a);
_putchar('\'');
_puts(equal_sign + 1);
_puts("'\n");
return (0);
}
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
if (info->argc == 1)
{
list_t *node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
}
else
{
for (int i = 1; info->argv[i]; i++)
{
char *equal_sign = _strchr(info->argv[i], '=');
if (equal_sign)

set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}
}
return (0);
}
