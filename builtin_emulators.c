#include "shell.h"
#include <stdio.h>

int my_exit(info_t *info)
{
if (info->argv[1]) {
int exit_code = _erratoi(info->argv[1]);
if (exit_code == -1)
{
info->status = 2;
print_error(info, "Illegal number: %s\n", info->argv[1]);
return (1);
}
info->err_num = exit_code;
}
else
{
info->err_num = -1;
}
return (-2);
}

int my_cd(info_t *info)
{
char *dir = info->argv[1];
char buffer[1024];

if (!dir)
{
dir = _getenv(info, "HOME=");
if (!dir)
dir = _getenv(info, "PWD=");
}
else if (_strcmp(dir, "-") == 0)
{
dir = _getenv(info, "OLDPWD=");
if (!dir) {
_puts(info->env->pwd);
_putchar('\n');
return (1);
}
_puts(dir);
_putchar('\n');
}

if (chdir(dir) == -1) {
perror("chdir");
return (1);
}

_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));

return (0);
}

int my_help(info_t *info)
{
_puts("Help call works. Function not yet implemented.\n");
return (0);
}
