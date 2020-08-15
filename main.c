#include "fdf.h"
#include <stdio.h>

void end(t_fdf *fdf)
{
    free_fdf(fdf);
    exit(0);
}


void shift_key(int key, t_fdf *data)
{
    if (key == 126)
        data->shift_y -= 30;
    if (key == 125)
        data->shift_y += 30;
    if (key == 123)
        data->shift_x -= 30;
    if (key == 124)
        data->shift_x += 30;
}

void zoom_key(int key, t_fdf *data)
{
    if (key == 69)
        data->zoom += 1;
    if (key == 78)
        if (data->zoom > 1)
            data->zoom -= 1;
}

int deal_key(int key, t_fdf *data)
{
    ft_printf("%d\n", key);
    if (key == 53 || key == 8 || key == 91 || key == 69 || key == 78 || key == 126 || key == 125 || key == 124 || key == 123 || key == 12 || key == 14) {
        if (key == 53)
            end(data);
        if (key == 8 || key == 91)
            data->isometric = data->isometric == 0 ? 1 : 0;
        shift_key(key, data);
        zoom_key(key, data);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        draw(data);
    }
    return (0);
}

void free_fdf(t_fdf *fdf)
{
    int i;

    if (fdf->mlx_ptr && fdf->win_ptr)
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    if (fdf->line)
        free(fdf->line);
    i = 0;
    if (fdf->matrix)
    {
        while (i <= fdf->height)
        {
            free(fdf->matrix[i]);
            fdf->matrix[i++] = NULL;
        }
        free(fdf->matrix);
    }
    free(fdf);
}



void		ft_error_t(char const *text)
{
    write(2, "Error\n", 6);
    write(2, text, ft_strlen(text));
    write(2, "\n", 1);
    exit(1);
}

t_fdf *init_fdf(void)
{
    t_fdf *fdf;

    if (!(fdf = malloc(sizeof(t_fdf))))
        ft_error_t("fdf init malloc");
    fdf->matrix = NULL;
    fdf->zoom = 2;
    fdf->shift_x = 500;
    fdf->shift_y = 500;
    fdf->isometric = 1;
    fdf->line = NULL;
    fdf->win_ptr = NULL;
    fdf->mlx_ptr = NULL;
    return (fdf);
}





void map_zoom(t_fdf *fdf) {
    if (fdf->height * fdf->width <= 100)
        fdf->zoom = 30;
    else if (fdf->height * fdf->width <= 250)
        fdf->zoom = 20;
    else if (fdf->height * fdf->width <= 500)
        fdf->zoom = 15;
    else if (fdf->height * fdf->width <= 1000)
        fdf->zoom = 10;
    else if (fdf->height * fdf->width <= 25000)
        fdf->zoom = 5;
    else if (fdf->height * fdf->width <= 100000)
        fdf->zoom = 4;
    else if (fdf->height * fdf->width <= 200000)
        fdf->zoom = 3;
    else if (fdf->height * fdf->width <= 300000)
        fdf->zoom = 2;
}

t_fdf *error_fdf(char const *text, int init)
{
    static t_fdf *fdf;
    if (init)
    {
        fdf = init_fdf();
        return (fdf);
    }
    free_fdf(fdf);
    ft_error_t(text);
    return (NULL);
}

void init_mlx(t_fdf *fdf) {
    if (!(fdf->mlx_ptr = mlx_init()))
        error_fdf("mlx init", 0);
    if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF")))
        error_fdf("mlx init", 0);
    if (!(fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT)))
        error_fdf("mlx init", 0);
    fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
}

int main(int argc, char **argv)
{
    t_fdf *data;

    if (argc == 2)
    {
        data = error_fdf(NULL, 1);
        read_map(argv[1], data);
        init_mlx(data);
        map_zoom(data);
        draw(data);
        mlx_key_hook(data->win_ptr, deal_key, data);
        mlx_loop(data->mlx_ptr);
        free_fdf(data);
    }
    else
        ft_printf("Usage :./fdf_original <filename>\n");
    return 0;
}
