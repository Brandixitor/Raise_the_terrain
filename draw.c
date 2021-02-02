#include "rtt.h"

/**
 * convert_iso - converts flat map into an isometric grid
 *
 * @data: the data structure
 */

void convert_iso(RTT_Data *data)
{
	int x, y = 0;
	int dx, dy, dz;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			dx = data->coord[y][x].x;
			dy = data->coord[y][x].y;
			dz = data->coord[y][x].z;

			data->coord[y][x].m_x = INCL * (dx - dy) + WIN_W / 2;
			data->coord[y][x].m_y = (1 - INCL) * (dx + dy) - dz + WIN_H / 2;
			x++;
		}
		y++;
	}
}

/**
 * init_zoom - gets the default zoom for the grid to be fit inside the window
 *
 * @data: the data structure
 */

void init_zoom(RTT_Data *data)
{
	int x, y;
	int zx, zy;

	while (1)
	{
		y = 0;
		while (y < data->height)
		{
			x = 0;
			while (x < data->width)
			{
				zx = WIN_W / 2 + ((data->coord[y][x].m_x - WIN_W / 2)
					* (data->zoom + 1)) / 100;
				zy = WIN_H / 2 + ((data->coord[y][x].m_y - WIN_H / 2)
					* (data->zoom + 1)) / 100;
				if (zx < PAD || zy < PAD)
					return;
				x++;
			}
			y++;
		}
		if (zx < WIN_W - PAD && zy < WIN_H - PAD)
			data->zoom++;
		else
			return;
	}

}

/**
 * update_grid - update the modifiable values of the grid
 *
 * @data: the data structure
 */

void update_grid(RTT_Data *data)
{
	int x, y = 0;
	int tx, ty, tz;
	float a = data->rot * M_PI / 180;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			tx = data->coord[y][x].xf;
			ty = data->coord[y][x].yf;
			tz = data->coord[y][x].zf;
			data->coord[y][x].x = tx * cos(a) - ty * sin(a);
			data->coord[y][x].y = tx * sin(a) + ty * cos(a);
			data->coord[y][x].z = (tz * data->z_mul) / 100;
			x++;
		}
		y++;
	}
	convert_iso(data);
}

/**
 * draw_grid - draws the grid in the window in isometric view
 *
 * @instance: the SDL2 instance
 * @data: the data structure
 */

void draw_grid(SDL_Instance instance, RTT_Data data)
{
	int x, y = 0;
	int fx, fy, tx1, ty1, tx2, ty2;

	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);

	while (y + 1 < data.height)
	{
		x = 0;
		while (x + 1 < data.width)
		{
			fx = WIN_W / 2 + ((data.coord[y][x].m_x - WIN_W / 2)
				* data.zoom) / 100;
			fy = WIN_H / 2 + ((data.coord[y][x].m_y - WIN_H / 2)
				* data.zoom) / 100;

			tx1 = WIN_W / 2 + ((data.coord[y + 1][x].m_x - WIN_W / 2)
				* data.zoom) / 100;
			ty1 = WIN_H / 2 + ((data.coord[y + 1][x].m_y - WIN_H / 2)
				* data.zoom) / 100;
			SDL_RenderDrawLine(instance.renderer, fx, fy, tx1, ty1);

			tx2 = WIN_W / 2 + ((data.coord[y][x + 1].m_x - WIN_W / 2)
				* data.zoom) / 100;
			ty2 = WIN_H / 2 + ((data.coord[y][x + 1].m_y - WIN_H / 2)
				* data.zoom) / 100;
			SDL_RenderDrawLine(instance.renderer, fx, fy, tx2, ty2);
			x++;
		}
		fx = WIN_W / 2 + ((data.coord[y][x].m_x - WIN_W / 2)
			* data.zoom) / 100;
		fy = WIN_H / 2 + ((data.coord[y][x].m_y - WIN_H / 2)
			* data.zoom) / 100;

		tx1 = WIN_W / 2 + ((data.coord[y + 1][x].m_x - WIN_W / 2)
			* data.zoom) / 100;
		ty1 = WIN_H / 2 + ((data.coord[y + 1][x].m_y - WIN_H / 2)
			* data.zoom) / 100;
		SDL_RenderDrawLine(instance.renderer, fx, fy, tx1, ty1);
		y++;
	}
	x = 0;
	while (x + 1 < data.width)
	{
		fx = WIN_W / 2 + ((data.coord[y][x].m_x - WIN_W / 2)
			* data.zoom) / 100;
		fy = WIN_H / 2 + ((data.coord[y][x].m_y - WIN_H / 2)
			* data.zoom) / 100;

		tx2 = WIN_W / 2 + ((data.coord[y][x + 1].m_x - WIN_W / 2)
			* data.zoom) / 100;
		ty2 = WIN_H / 2 + ((data.coord[y][x + 1].m_y - WIN_H / 2)
			* data.zoom) / 100;
		SDL_RenderDrawLine(instance.renderer, fx, fy, tx2, ty2);
		x++;
	}
}
