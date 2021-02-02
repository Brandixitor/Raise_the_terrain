#include "rtt.h"

/**
 * count_rows - returns the number of rows in a line
 *
 * @line: the line to count rows of
 *
 * Return: the number of rows in the line line
 */

int count_rows(char *line)
{
	int i = 0, count = 1;

	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

/**
 * delete_data - frees the data structure
 *
 * @data: the data structure
 */

void delete_data(RTT_Data *data)
{
	int y = data->height - 1;

	if (data->coord)
	{
		while (y != 0)
			free(data->coord[y--]);
		free(data->coord);
	}
}
