#include "shell.h"
#include <limits.h> /** Include necessary libraries */

/**
 * err_atoi - Convert a string to an integer with error handling.
 * @s: The string to be converted.
 * Return: The converted integer if successful, or -1 on error.
 */
int err_atoi(const char *s)
{
long int result = 0;
int i = 0;

if (*s == '+')
s++;

for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX || result < INT_MIN)
return (-1); /** Overflow or underflow */
}
else
return (-1); /** Non-numeric character */
}
return (int)(result);
}

/**
 * print_error_message - Print an error message to stderr.
 * @info: The parameter & return info structure.
 * @error_type: The string containing the specified error type.
 */
void print_error_message(info_t *info, const char *error_type)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_type);
}

/**
 * print_integer - Print an integer to a given file descriptor.
 * @value: The integer to print.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_integer(int value, int fd)
{
int count = 0;
int sign = 1;

if (fd == STDERR_FILENO)
{
sign = -1;
}

if (value < 0)
{
_eputchar('-');
count++;
value = -value;
}

if (value == 0)
{
_putchar('0');
count++;
}
else
{
int reversed = 0;
while (value > 0)
{
reversed = reversed * 10 + value % 10;
value /= 10;
}
while (reversed > 0)
{
_putchar(reversed % 10 + '0');
reversed /= 10;
count++;
}
}

return (count);
}

/**
 * convert_to_base - Convert a number to a specified base and return it 
 * as a string.
 * @num: The number to convert.
 * @base: The base to use for conversion.
 * @flags: Argument flags.
 * Return: The converted number as a string.
 */
char *convert_to_base(long int num, int base, int flags)
{
static char buffer[50];
char *ptr = &buffer[49];
unsigned long n = num;
char sign = 0;
char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : 
"0123456789ABCDEF";

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}

*ptr = '\0';

do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
{
*--ptr = sign;
}

return ptr;
}

/**
 * remove_first_comment - Replace the first '#' character with '\0'.
 * @buf: The address of the string to modify.
 */
void remove_first_comment(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
}
