#include "shell.h"
#include <stdio.h>

/**
 * my_exit - Exit the shell with a given exit status
 * @info: Structure containing potential arguments.
 * Return: Exits with the specified exit status.
 */
int my_exit(info_t *info)
{
if (info->argv[1])
{
int exit_code = _erratoi(info->argv[1]);
if (exit_code == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return 1;
}
info->err_num = exit_code;
}
else
{
info->err_num = -1;
}
return -2;
}

/**
 * my_cd - Change the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_cd(info_t *info)
{
char *s, *dir;
char buffer[1024];
int chdir_ret;

s = getcwd(buffer, sizeof(buffer));
if (!s)
{
perror("getcwd"); // Print error message
}

if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
dir = _getenv(info, "OLDPWD=");
if (!dir)
{
_puts(s);
_putchar('\n');
return 1;
}
_puts(dir);
_putchar('\n');
chdir_ret = chdir(dir);
}
else
{
chdir_ret = chdir(info->argv[1]);
}

if (chdir_ret == -1)
{
perror("chdir");
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
}
return 0;
}

/**
 * my_help - Display a help message.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_help(info_t *info)
{
char **arg_array = info->argv;
_puts("Help call works. Function not yet implemented.\n");
if (0)
{
_puts(*arg_array);
}
return 0;
}
