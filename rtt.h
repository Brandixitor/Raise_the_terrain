#ifndef RTT_H
#define RTT_H

#include <SDL2/SDL.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define INCL 0.7
#define ESP 100
#define PAD 50

#define WIN_W 1260
#define WIN_H 720

/**
 * struct SDL_Instance - the SDL2 instance structure
 *
 * @window: the window pointer
 * @renderer: the renderer pointer
 */

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct RTT_Point - the Point structure
 *
 * @x: the x value of the point
 * @y: the y value of the point
 * @z: the z value of the point
 * @xf: the fixed x value of the point
 * @yf: the fixed y value of the point
 * @zf: the fixed z value of the point
 * @m_x: the modified x value of the point
 * @m_y: the modified y value of the point
 */

typedef struct RTT_Point
{
	int x;
	int y;
	int z;
	int xf;
	int yf;
	int zf;
	double m_x;
	double m_y;
} RTT_Point;

/**
 * struct RTT_Data - the Data structure
 *
 * @instance: the SDL2 Instance
 * @coord: the array of Points constituates the grid
 * @width: the Width of the grid
 * @height: the Height of the grid
 * @zoom: the Zoom of the grid
 * @rot: the Rotation of the grid
 * @z_mul: the Z Multiplier of the grid
 */

typedef struct RTT_Data
{
	SDL_Instance instance;
	RTT_Point **coord;
	int width;
	int height;
	int zoom;
	int rot;
	int z_mul;
} RTT_Data;

/* DRAW */
void convert_iso(RTT_Data *data);
void draw_grid(SDL_Instance instance, RTT_Data data);
void init_zoom(RTT_Data *data);
void update_grid(RTT_Data *data);

/* EVENTS */
int poll_events(RTT_Data *data);

/* INIT */
int init(RTT_Data *data, char *filename);
int check_file(FILE *fp, char *filename);
int init_instance(SDL_Instance *);
int init_data(RTT_Data *data, FILE *fp);
int init_file(RTT_Data *data, FILE *fp);

/* UTILS */
int count_rows(char *line);
void delete_data(RTT_Data *data);

/* DEBUG */
void print_data(RTT_Data *data);

#endif
