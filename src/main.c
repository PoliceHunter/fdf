/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:11:13 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/29 12:16:24 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_fdf	*init_fdf(void)
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

void	map_zoom(t_fdf *fdf)
{
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

t_fdf	*error_fdf(char const *text, int init)
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

void	init_mlx(t_fdf *fdf)
{
	if (!(fdf->mlx_ptr = mlx_init()))
		error_fdf("mlx init", 0);
	if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF")))
		error_fdf("mlx init", 0);
	if (!(fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT)))
		error_fdf("mlx init", 0);
	fdf->data_addr = mlx_get_data_addr(fdf->img,
			&(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
}

int		main(int argc, char **argv)
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
	return (0);
}
