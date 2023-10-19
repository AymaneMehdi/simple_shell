#include "shell.h"

/* Function prototypes */
void clear_info(info_t *info);
int interactive(info_t *info);
ssize_t get_input(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int history_flag);
void write_history(info_t *info);
char *find_path(info_t *info, char *path, char *command);
int is_cmd(info_t *info, char *command);
char **get_environ(info_t *info);
void print_error(info_t *info, char *message);
void _myexit(info_t *info);
int _myenv(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int _mycd(info_t *info);
int _myalias(info_t *info);
void fork_cmd(info_t *info);

int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

int find_builtin(info_t *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

void find_cmd(info_t *info)
{
char *path = NULL;

    /**(rest of your find_cmd implementation) */

if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
/**(rest of your find_cmd implementation) */
}
}

void fork_cmd(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
