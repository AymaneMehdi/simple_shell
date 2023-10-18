#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT }; // Initialize an info_t structure
int fd = 2; // Initialize a file descriptor, default to stderr (2)

// Inline assembly to manipulate the file descriptor value
asm (
"mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd)
);

// Check if the program was given an additional argument (file to read)
if (ac == 2)
{
fd = open(av[1], O_RDONLY); // Attempt to open the specified file
if (fd == -1)
{
if (errno == EACCES)
exit(126); // Exit with code 126 if permission denied
if (errno == ENOENT)
{
// Print an error message and exit with code 127 if the file doesn't exist
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE); // Return failure status on other errors
}
info->readfd = fd; // Set the read file descriptor in the info structure
}

populate_env_list(info); // Populate environment variables list
read_history(info); // Read command history from a file
hsh(info, av); // Start the shell (command interpreter)

return (EXIT_SUCCESS); // Return success status
}
