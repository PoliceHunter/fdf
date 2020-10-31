/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:45:40 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/29 12:46:11 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_key(int key, t_fdf *data)
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

void	zoom_key(int key, t_fdf *data)
{
	if (key == 69)
		data->zoom += 1;
	if (key == 78)
		if (data->zoom > 1)
			data->zoom -= 1;
}

int		deal_key(int key, t_fdf *data)
{
	ft_printf("%d\n", key);
	if (key == 53 || key == 8 || key == 91 || key == 69 || key == 78 ||
			key == 126 || key == 125 || key == 124
			|| key == 123 || key == 12 || key == 14)
	{
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
