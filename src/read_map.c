/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:21:04 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/31 16:22:22 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_height(char *file_name, t_fdf *fdf)
{
	int fd;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		error_fdf("set_width open file error", 0);
	fdf->height = 0;
	while (get_next_line(fd, &fdf->line))
	{
		if (fdf->line == NULL)
			error_fdf("set_width gnl malloc", 0);
		fdf->height++;
		free(fdf->line);
	}
	close(fd);
}

void	get_width(char *filename, t_fdf *fdf)
{
	int fd;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		error_fdf("set_width file open error", 0);
	fdf->width = 0;
	while (get_next_line(fd, &fdf->line))
	{
		if (fdf->line == NULL)
		{
			error_fdf("set width with malloc", 0);
			close(fd);
		}
		if (fdf->width != 0 && count_words(fdf->line, ' ')
				!= (size_t)fdf->width)
		{
			error_fdf("invalid map width", 0);
			close(fd);
		}
		fdf->width = fdf->width == 0 ? count_words(fdf->line, ' ') : fdf->width;
		free(fdf->line);
	}
	close(fd);
}

void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	nums = ft_strsplit(line, ' ');
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	read_map(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	get_height(file_name, data);
	get_width(file_name, data);
	data->matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	i = 0;
	while (i <= data->height)
		if (!(data->matrix[i++] =
					(int *)malloc(sizeof(int) * (data->width + 1))))
			error_fdf("matrix malloc", 0);
	fd = open(file_name, O_RDONLY, 0);
	i = 0;
	while (get_next_line(fd, &line))
	{
		fill_matrix(data->matrix[i], line);
		free(line);
		i++;
	}
	close(fd);
	data->matrix[i] = NULL;
}
