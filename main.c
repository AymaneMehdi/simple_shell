#include "shell.h"

int main(int argc, char **argv)
{
info_t info = INFO_INIT;
int fd = 2;

fd += 3;

if (argc == 2)
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
{
exit(126);
}
if (errno == ENOENT)
{
fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
exit(127);
}
return EXIT_FAILURE;
}
info.readfd = fd;
}

populate_env_list(&info);
read_history(&info);
hsh(&info, argv);

return EXIT_SUCCESS;
}
