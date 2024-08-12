#include "_getline.h"

static char buffer[READ_SIZE + 1];
static int buf_pos;
static int bytes_read;

/**
 * allocate_line - Allocates and appends a character to the line
 * @line: Current line string
 * @line_len: Current length of the line
 * @c: Character to append
 * Return: Pointer to the modified line, or NULL on failure
 */
char *allocate_line(char *line, int line_len, char c)
{
	char *temp;

	temp = realloc(line, line_len + 2);
	if (temp == NULL)
	{
		free(line);
		return (NULL);
	}
	line = temp;
	line[line_len] = c;
	line[line_len + 1] = '\0';
	return (line);
}

/**
 * process_line - Processes input from the buffer into lines
 * @fd: File descriptor to read from
 * @line: Current line string
 * @line_len: Current length of the line
 * Return: The complete line without newline character, or NULL
 */
char *process_line(const int fd, char *line, int line_len)
{
	while (1)
	{
		if (buf_pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, READ_SIZE);
			if (bytes_read <= 0)
				return (NULL);
			buf_pos = 0;
		}

		while (buf_pos < bytes_read)
		{
			char c = buffer[buf_pos++];

			line = allocate_line(line, line_len++, c);
			if (line == NULL)
				return (NULL);
			if (c == '\n')
			{
				line[--line_len] = '\0';
				return (line);
			}
		}
	}

	if (line_len == 0)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * _getline - Reads an entire line from a file descriptor
 * @fd: The file descriptor to read from
 * Return: A null-terminated string that does not include
 * the newline character, or NULL
 */
char *_getline(const int fd)
{
	char *line = NULL;
	int line_len = 0;

	if (fd < 0)
		return (NULL);

	line = malloc(1);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';

	return (process_line(fd, line, line_len));
}
