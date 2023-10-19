#include "shell.h"
#include <stdio.h>

/**
 * my_exit - Set error-related values in the 'info' structure based on
 * command-line arguments.
 * This function is responsible for managing program exit statuses and
 * error conditions.
 * It takes a pointer to an 'info_t' structure as a parameter, which is
 * expected to contain relevant program information. The function performs
 * the following actions:
 * - If a command-line argument exists at index 1, it attempts to convert it
 * into an integer and sets 'exit_code' accordingly.
 * - If 'exit_code' is -1, the 'info' structure's 'status' is set to 2,
 * indicating an error, and an error message is printed. The function
 * returns 1 to signify an error exit.
 * - If 'exit_code' is a valid integer, it sets the 'err_num' field in
 * the 'info' structure.
 * - If no command-line argument is found at index 1, 'err_num' is set to -1,
 * indicating the absence of a specific error number.
 *
 * Return Value:
 * The function returns -2, and the interpretation of this return value
 * depends on the larger context within which the function is used.
 */
int my_exit(info_t *info)
{
if (info->argv[1])
{
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

/**
 * my_cd - Change the current working directory.
 *
 * This function changes the current working directory based on the provided
 * directory path.
 * If no directory path is given, it attempts to change to the user's
 * home directory or the present working directory as appropriate.
 * If the provided directory path is "-", it changes to the previous working
 * directory.
 * @info: Parameter structure.
 *
 * Return:
 * - 0 on success.
 * - 1 on error (with an error message printed in the case of chdir failure).
 */
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
if (!dir)
{
_puts(info->env->pwd);
_putchar('\n');
return (1);
}
_puts(dir);
_putchar('\n');
}

if (chdir(dir) == -1)
{
perror("chdir");
return (1);
}

_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));

return (0);
}

/**
 * my_help - Display a help message (placeholder).
 *
 * This function is a placeholder for displaying a help message.
 * It currently prints a message indicating that the help functionality
 * is not yet implemented.
 * @info: Parameter structure.
 *
 * Return:
 * Always returns 0 to signify that the function has been called.
 */
int my_help(info_t *info)
{
_puts("Help call works. Function not yet implemented.\n");
return (0);
}
