//
// Created by Taisha Myrcella on 8/12/20.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "libft/inc/libft.h"
#include "minilibx_macos/mlx.h"
#include <math.h>
#include <fcntl.h>


#define WIDTH 1080
#define MENU_WIDTH 250
#define HEIGHT 1920
#define BACKGROUND 0x222222
#define MENU_BACKGROUND 0x1E1E1E


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

typedef struct s_fdf t_fdf;
struct s_fdf
{
    int width;
    int height;
    int **matrix;
    int zoom;
    int color;
    int shift_x;
    int shift_y;
    int isometric;
    int bits_per_pixel;
    int size_line;
    int endian;
    char *data_addr;
    char *line;


    void *img;
    void *mlx_ptr;
    void *win_ptr;
};

typedef struct	s_cord
{
    float	x;
    float	y;
}				t_cord;


void read_map(char *file_name, t_fdf *data);
void bresenham(t_cord cords, float x1, float y1, t_fdf *data);
void draw(t_fdf *data);
t_fdf *error_fdf(char const *text, int init);
void free_fdf(t_fdf *fdf);
static void 	rotate_x(float *y, float *z, int alpha);


#endif //FDF_FDF_H
