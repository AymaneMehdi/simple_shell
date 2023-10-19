#include "shell.h"

/**
 * is_chain - Test if the current character in the buffer is a chain delimiter
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: The address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = '\0';
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = '\0';
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found the end of this command */
{
buf[j] = '\0'; /* replace semicolon with null terminator */
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}
*p = j;
return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on the last status
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: The address of the current position in buf
 * @i: The starting position in buf
 * @len: The length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = '\0';
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = '\0';
j = len;
}
}

*p = j;
}

/**
 * replace_alias - Replaces aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
for (int i = 0; info->argv[i]; i++)
{
char *arg = info->argv[i];

if (arg[0] == '$' && arg[1])
{
if (!_strcmp(arg, "$?"))
{
replace_string(&info->argv[i], _strdup(convert_number(info->status, 10, 0)));
}
else if (!_strcmp(arg, "$$"))
{
replace_string(&info->argv[i], _strdup(convert_number(getpid(), 10, 0)));
}
else
{
list_t *node = node_starts_with(info->env, &arg[1], '=');
if (node)
{
char *value = _strchr(node->str, '=');
if (value)
{
replace_string(&info->argv[i], _strdup(value + 1));
}
}
else
{
replace_string(&info->argv[i], _strdup(""));
}
}
}
}
return (0);
}

/**
 * replace_string - Replaces a string
 * @old: The address of the old string
 * @new: The new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
