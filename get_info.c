#include "shell.h"

/**
 * init_info - Initializes the info_t structure.
 * @info: The structure address to initialize.
 */
void init_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
info->fname = NULL; // Initialize other fields as needed
}

/**
 * set_info - Initializes the info_t structure with provided arguments.
 * @info: The structure address.
 * @arg: The argument string.
 * @av: The argument vector.
 */
void set_info(info_t *info, char *arg, char **av)
{
info->arg = arg;
info->fname = av[0];

if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
info->argc = count_elements(info->argv);
replace_alias(info);
replace_vars(info);
}
}

/**
 * free_info - Frees memory associated with the info_t structure.
 * @info: The structure address.
 * @all: Set to true if freeing all fields.
 */
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}
