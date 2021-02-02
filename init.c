#include "rtt.h"

/**
 * init - dispatch the initiation process (data validation, parsing)
 *
 * @data: the RTT_Data structure containing main data
 * @filename: the name of the given file to open fp later
 *
 * Return: 0 if success, 1 on error
 */

int init(RTT_Data *data, char *filename)
{
	FILE *fp;

	fp = fopen(filename, "r");

	if (check_file(fp, filename) != 0)
		return (1);
	if (init_data(data, fp) != 0)
		return (1);

	fseek(fp, 0, SEEK_SET);
	if (init_file(data, fp) != 0)
		return (1);
	fclose(fp);

	return (0);
}

/**
 * check_file - checks if the file exists and if it's a regular file
 *
 * @fp: the file pointer associated to the file
 * @filename: the name of the given file
 *
 * Return: 0 if success, 1 on error
 */

int check_file(FILE *fp, char *filename)
{
	struct stat stat;

	if (lstat(filename, &stat) != 0)
		return (1);
	if (fp == NULL || !S_ISREG(stat.st_mode) || stat.st_mode & S_IXUSR)
	{
		fprintf(stderr, "Error: can't open the file %s\n", filename);
		return (1);
	}
	return (0);
}

/**
 * init_instance - initializes the SDL2 instance
 *
 * @instance: the SDL2 instance to initialize
 *
 * Return: 0 if success, 1 on error
 */

int init_instance(SDL_Instance *instance)
{
	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Create a new Window instance */
	instance->window = SDL_CreateWindow(
		"Raise the Terrain - Holberton School Project",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* Create a new Renderer instance linked to the window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

/**
 * init_data - fill up the data structure, waiting for points to
 * be filled later
 *
 * @data: the RTT_Data structure
 * @fp: the file pointer associated to the file
 *
 * Return: 0 if success, 1 on error
 */

int init_data(RTT_Data *data, FILE *fp)
{
	char *line = NULL;
	int line_count = 0;
	size_t len = 0, read;

	if (init_instance(&data->instance) != 0)
		return (1);

	while ((read = getline(&line, &len, fp) != -1))
		line_count++;
	free(line);
	data->coord = malloc(sizeof(RTT_Point *) * line_count);
	if (data->coord == NULL)
		return (1);

	data->width = 0;
	data->height = line_count;

	data->zoom = 1;
	data->z_mul = 100;
	return (0);
}

/**
 * init_file - converts the input file into RTT_Point's arrays
 *
 * @data: the RTT_Data structure
 * @fp: the file pointer associated to the file
 *
 * Return: 0 if success, 1 on error
 */

int init_file(RTT_Data *data, FILE *fp)
{
	char *line = NULL, *tmp = NULL;
	size_t len = 0, read;
	int y = 0, x;

	while (y < data->height)
	{
		read = getline(&line, &len, fp);
		data->width = count_rows(line);
		data->coord[y] = malloc(sizeof(RTT_Point) * data->width);
		if (data->coord[y] == NULL)
			return (1);
		x = 0;
		while ((tmp = strtok(x == 0 ? line : NULL, " ")))
		{
			data->coord[y][x].xf = x * ESP - (data->width - 1) * (ESP / 2);
			data->coord[y][x].yf = y * ESP - (data->height - 1) * (ESP / 2);
			data->coord[y][x].zf = atoi(tmp);
			data->coord[y][x].x = data->coord[y][x].xf;
			data->coord[y][x].y = data->coord[y][x].yf;
			data->coord[y][x].z = data->coord[y][x].zf;
			data->coord[y][x].m_x = 0;
			data->coord[y][x].m_y = 0;
			x++;
		}
		y++;
	}
	return (0);
}
