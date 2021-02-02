#include "rtt.h"

/**
 * print_data - a debug function printing grid and some other data in console
 *
 * @data: the data structure
 */

void print_data(RTT_Data *data)
{
	int y = 0, x;

	printf("Instance window address: %p\n", (void *)data->instance.window);
	printf("Instance renderer address: %p\n\n", (void *)data->instance.renderer);

	while (y < data->height)
	{
		x = 0;
		while (x < 8 * data->width)
		{
			x++;
			printf("-");
		}
		printf("-\n");
		x = 0;
		while (x < data->width)
		{
			printf("| %4d  ", data->coord[y][x].z);
			x++;
		}
		printf("|\n");
		y++;
	}
	x = 0;
	while (x < 8 * data->width)
	{
		x++;
		printf("-");
	}
	printf("-\n");
	printf("(Grid: %d x %d)\n", data->width, data->height);

	printf("\nData Informations:\n");
	printf("\tInitial Zoom: %d px\n", data->zoom);
}
