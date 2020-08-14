#include "fdf.h"
#include <stdio.h>


void shift_key(int key, fdf *data)
{
    if (key == 30)
        data->shift_step += 10;
    if (key == 33)
        data->shift_step -= 10;
    if (key == 126 || key == 13)
        data->shift_y -= data->shift_step;
    if (key == 125 || key == 1)
        data->shift_y += data->shift_step;
    if (key == 123 || key == 0)
        data->shift_x -= data->shift_step;
    if (key == 124 || key == 2)
        data->shift_x += data->shift_step;
}

void zoom_key(int key, fdf *data)
{
    if (key == 69)
        data->zoom += 10;
    if (key == 78)
        data->zoom -= 10;
}

int deal_key(int key, fdf *data)
{
    ft_printf("%d\n", key);
    shift_key(key, data);
    zoom_key(key, data);
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw(data);
    return (0);
}


int main(int argc, char **argv)
{
    fdf *data;

    data = (fdf*)malloc(sizeof(fdf));
    read_map(argv[1], data);
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
    data->zoom = 20;
    data->shift_step = 35;
    draw(data);
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);

    return 0;
}
