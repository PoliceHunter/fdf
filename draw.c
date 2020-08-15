//
// Created by Taisha Myrcella on 8/12/20.
//

#include "fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)


static void	draw_background(t_fdf *fdf)
{
    int	*image;
    int	i;

    ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
    image = (int *)(fdf->data_addr);
    i = 0;
    while (i < HEIGHT * WIDTH)
    {
        image[i] = (i % WIDTH < MENU_WIDTH) ? MENU_BACKGROUND : BACKGROUND;
        i++;
    }
}

void isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.82);
	*y = (*x + *y) * sin(0.82) - z;

}

void print_menu(t_fdf *data) {
    int y;
    void *mlx;
    void *win;

    y = 0;
    mlx = data->mlx_ptr;
    win = data->win_ptr;
    mlx_string_put(mlx, win, 65, y += 20, 0xffffff, "How to Use");
    mlx_string_put(mlx, win, 15, y += 35, 0xffffff, "Zoom: +/-");
    mlx_string_put(mlx, win, 15, y += 30, 0xffffff, "Move: Arrows");
    mlx_string_put(mlx, win, 15, y += 30, 0xffffff, "Projection: C/8");
}

float mod(float n)
{
    return (n < 0 ? n * -1 : n);
}

t_cord get_step(t_cord cords, float x1, float y1)
{
    t_cord  step;
    float max;

    step.x = x1 - cords.x;
    step.y = y1 - cords.y;
    max = mod(step.x) > mod(step.y) ? mod(step.x) : mod(step.y);
    step.x /= max;
    step.y /= max;
    return (step);
}


void my_put_pixel(t_fdf *fdf, int x, int y, int color)
{
    int i;
    if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
        fdf->data_addr[i] = color;
        i++;
        fdf->data_addr[i] = color >> 8;
        i++;
        fdf->data_addr[i] = color >> 16;
    }
}


void put_pixel(t_cord cords, float x1, float y1, t_fdf *fdf)
{
    t_cord step;

    step = get_step(cords, x1, y1);
    while ((int)(x1 - cords.x) || (int)(y1 -cords.y))
    {
        my_put_pixel(fdf, cords.x, cords.y, fdf->color);
        cords.x += step.x;
        cords.y += step.y;
    }
}


void bresenham(t_cord cords, float x1, float y1, t_fdf *data)
{
	int z;
	int z1;

	z = data->matrix[(int)cords.y][(int)cords.x] * data->zoom;
	z1 = data->matrix[(int)y1][(int)x1] * data->zoom;

	cords.x *= data->zoom;
	cords.y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;

	if (data->isometric)
    {
        isometric(&cords.x, &cords.y, z);
        isometric(&x1, &y1, z1);
    }

	data->color = (z || z1) ? C_AQUAMARINE : C_WHI;
    cords.x += data->shift_x;
    cords.y += data->shift_y;
    y1 += data->shift_y;
    x1 += data->shift_x;
    put_pixel(cords, x1, y1, data);
}

void draw(t_fdf *data)
{
    t_cord cords;

	cords.y = 0;
    draw_background(data);
	while (cords.y < data->height)
	{
		cords.x = 0;
		while (cords.x < data->width)
		{
			if (cords.x < data->width - 1)
				bresenham(cords, cords.x + 1, cords.y, data);
			if (cords.y < data->height - 1)
				bresenham(cords, cords.x, cords.y + 1, data);
            cords.x++;
		}
        cords.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	print_menu(data);
}
