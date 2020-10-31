/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:45:01 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/29 12:45:29 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	end(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(0);
}

void	free_fdf(t_fdf *fdf)
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

void	ft_error_t(char const *text)
{
	write(2, "Error\n", 6);
	write(2, text, ft_strlen(text));
	write(2, "\n", 1);
	exit(1);
}
