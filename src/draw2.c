/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:43:56 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/29 12:51:53 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_background(t_fdf *fdf)
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

void		isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.82);
	*y = (*x + *y) * sin(0.82) - z;
}

void		print_menu(t_fdf *data)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = data->mlx_ptr;
	win = data->win_ptr;
	mlx_string_put(mlx, win, 65, y += 20, 0xffffff, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, 0xffffff, "Zoom: +/-");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffff, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffff, "Projection: C/8");
}

float		mod(float n)
{
	return (n < 0 ? n * -1 : n);
}
