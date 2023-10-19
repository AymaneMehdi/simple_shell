#include "shell.h"


/**
 * input_buf - Reads input into a buffer and handles command chaining.
 * @info: The parameter structure.
 * @buf: The address of the buffer.
 * @len: The address of the len var.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* If nothing left in the buffer, fill it */
{
/* Free the previous buffer */
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(info, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* Remove trailing newline */
r--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);

/* Check for command chaining here */
if (_strchr(*buf, ';'))
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}


/**
 * get_input - Gets the next line of input from the user or command
 * chain buffer.
 * @info: The parameter structure.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
static char *buf; /* The ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH); /* Flush the output buffer */
r = input_buf(info, &buf, &len); /* Read input into the buffer */

if (r == -1) /* EOF (end of file), indicating the end of input */
return (-1);

if (len) /* If there are commands left in the chain buffer */
{
j = i; /* Initialize a new iterator to the current buffer position */
p = buf + i; /* Get a pointer for return */

check_chain(info, buf, &j, i, len); /* Check for command chaining */
while (j < len) /* Iterate to semicolon or end of buffer */
{
if (is_chain(info, buf, &j))
break;
j++;
}

i = j + 1; /* Increment past the nulled ';' */
if (i >= len) /* If reached the end of the buffer */
{
i = len = 0; /* Reset the position and length */
info->cmd_buf_type = CMD_NORM;
}

*buf_p = p; /* Pass back the pointer to the current command position */
return (_strlen(p)); /* Return the length of the current command */
}

*buf_p = buf; /* If not a chain, pass back the buffer from _getline() */
return (r); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Reads data from a file descriptor into a buffer.
 * @info: The parameter structure.
 * @buf: The buffer to read into.
 * @i: The current size of the buffer.
 *
 * Return: The number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i) /* If there are bytes left in the buffer, don't read again */
return (0);

/* Read from the file descriptor into the buffer */
r = read(info->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r; /* Update the current size of the buffer */

return (r);
}


/**
 * _getline - Gets the next line of input from STDIN.
 * @info: The parameter structure.
 * @ptr: The address of a pointer to the buffer, preallocated or NULL.
 * @length: The size of the preallocated ptr buffer if not NULL.
 *
 * Return: Length of the line read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* Memory allocation failure */
return (p ? (free(p), -1) : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
