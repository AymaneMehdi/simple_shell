#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
    char *dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    char *filename = malloc(strlen(dir) + strlen(HIST_FILE) + 2);
    if (!filename)
        return NULL;

    sprintf(filename, "%s/%s", dir, HIST_FILE);
    return filename;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return -1;

    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(filename);
    if (fd == -1)
        return -1;

    for (int i = 0; i < info->histcount; ++i)
    {
        dprintf(fd, "%s\n", info->history[i]);
    }

    close(fd);
    return 1;
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename)
        return 0;

    int fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;

    struct stat st;
    if (fstat(fd, &st) == -1 || st.st_size < 1)
    {
        close(fd);
        return 0;
    }

    char *buf = malloc(st.st_size + 1);
    if (!buf)
    {
        close(fd);
        return 0;
    }

    ssize_t rdlen = read(fd, buf, st.st_size);
    close(fd);
    if (rdlen <= 0)
    {
        free(buf);
        return 0;
    }

    buf[rdlen] = '\0';
    char *line = strtok(buf, "\n");
    int linecount = 0;

    while (line != NULL && linecount < HIST_MAX)
    {
        info->history[info->histcount++] = strdup(line);
        if (!info->history[info->histcount - 1])
        {
            free(buf);
            return 0;
        }

        ++linecount;
        line = strtok(NULL, "\n");
    }

    free(buf);
    return info->histcount;
}

/**
 * build_history_list - adds entry to history array
 * @info: Structure containing potential arguments.
 * @buf: buffer
 *
 * Return: 1 on success, else 0
 */
int build_history_list(info_t *info, char *buf)
{
    if (info->histcount >= HIST_MAX)
        return 0;

    info->history[info->histcount++] = strdup(buf);
    return info->history[info->histcount - 1] ? 1 : 0;
}

/**
 * renumber_history - renumbers the history array after changes
 * @info: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
    for (int i = 0; i < info->histcount; ++i)
    {
        free(info->history[i]);
    }
    return 0;
}
