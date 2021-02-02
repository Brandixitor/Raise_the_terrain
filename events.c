#include "rtt.h"

/**
 * poll_events - handles the keyboard events
 *
 * @data: the data structure
 *
 * Return: 1 if exit is needed, 0 else
 */

int poll_events(RTT_Data *data)
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	(void)data;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			if (key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return (1);
			if (key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
				data->zoom += 2;
			if (key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
				data->zoom -= 2;
			if (key.keysym.scancode == SDL_SCANCODE_UP)
				data->z_mul += 2;
			if (key.keysym.scancode == SDL_SCANCODE_DOWN)
				data->z_mul -= 2;
			if (key.keysym.scancode == SDL_SCANCODE_RIGHT)
				data->rot += 2;
			if (key.keysym.scancode == SDL_SCANCODE_LEFT)
				data->rot -= 2;
			break;
		}
	}
	return (0);
}
