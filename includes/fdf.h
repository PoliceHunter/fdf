/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:23:22 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/10/31 16:21:45 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/inc/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 1080
# define MENU_WIDTH 250
# define HEIGHT 1920
# define BACKGROUND 0x222222
# define MENU_BACKGROUND 0x1E1E1E

# define MAX_INT 2147483647
# define MIN_INT -2147483648

# define C_BLA 0x000000
# define C_BLU 0x0000ff
# define C_GRE 0x00ff00
# define C_RED 0xff0000
# define C_WHI 0xffffff
# define C_GOLD_PALE 0x00ffe7ba
# define C_GREEN_DARK 0x00006400
# define C_AQUAMARINE 0x007fffd4
# define C_PURPLE_DARK 0x00551a8b
# define C_ORANGE_DARK 0x008b2500
# define C_BROWNIE 0x0054291a
# define C_BLUE_NAVY 0x00000080
# define C_BLUE_DARK 0x00000020
# define C_LIGHT_RED 0x00ff4444

typedef struct s_fdf	t_fdf;
struct	s_fdf
{
	int		width;
	int		height;
	int		**matrix;
	int		zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	int		isometric;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data_addr;
	char	*line;
	void	*img;
	void	*mlx_ptr;
	void	*win_ptr;
};

typedef struct s_cord	t_cord;
struct	s_cord
{
	float	x;
	float	y;
};

void	init_mlx(t_fdf *fdf);
t_fdf	*error_fdf(char const *text, int init);
void	map_zoom(t_fdf *fdf);
t_fdf	*init_fdf(void);
void	end(t_fdf *fdf);
void	free_fdf(t_fdf *fdf);
void	ft_error_t(char const *text);
int		deal_key(int key, t_fdf *data);
void	zoom_key(int key, t_fdf *data);
void	shift_key(int key, t_fdf *data);
void	draw(t_fdf *data);
void	bresenham(t_cord cords, float x1, float y1, t_fdf *data);
void	put_pixel(t_cord cords, float x1, float y1, t_fdf *fdf);
void	my_put_pixel(t_fdf *fdf, int x, int y, int color);
t_cord	get_step(t_cord cords, float x1, float y1);
float	mod(float n);
void	print_menu(t_fdf *data);
void	isometric(float *x, float *y, int z);
void	draw_background(t_fdf *fdf);
void	read_map(char *file_name, t_fdf *data);
void	fill_matrix(int *z_line, char *line);
void	get_width(char *filename, t_fdf *fdf);
void	get_height(char *file_name, t_fdf *fdf);

#endif
