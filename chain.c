#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
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
else if (buf[j] == ';')
{
buf[j] = '\0';
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return 0;
}

*p = j;
return 1;
}

/**
 * check_chain - checks if the shell should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len) {
size_t j = *p;

if ((info->cmd_buf_type == CMD_AND && info->status) ||
(info->cmd_buf_type == CMD_OR && !info->status)) {
buf[i] = '\0';
j = len;
}

*p = j;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info) {
list_t *node = node_starts_with(info->alias, info->argv[0], '=');
if (node) {
char *p = _strchr(node->str, '=');
if (p) {
replace_string(&info->argv[0], _strdup(p + 1));
return 1;
}
}
return 0;
}

/**
 * replace_vars - replaces environment variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info) {
for (int i = 0; info->argv[i]; i++) {
if (info->argv[i][0] == '$' && info->argv[i][1] != '\0') {
char *var_name = &info->argv[i][1];
char *env_value = _getenv(info, var_name);
if (env_value != NULL) {
replace_string(&info->argv[i], _strdup(env_value));
} else {
replace_string(&info->argv[i], _strdup(""));
}
}
}
return 0;
}

/**
 * replace_string - replaces old string with new string
 * @old: address of old string pointer
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new) {
free(*old);
*old = new;
return 1;
}
