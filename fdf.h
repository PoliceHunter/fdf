//
// Created by Taisha Myrcella on 8/12/20.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "libft/inc/libft.h"
#include "minilibx_macos/mlx.h"
#include <math.h>

typedef struct
{
    int width;
    int height;
    int **matrix;
    int zoom;
    int color;
    int shift_x;
    int shift_y;
    int shift_step;

    void *mlx_ptr;
    void *win_ptr;
}           fdf;

void read_map(char *file_name, fdf *data);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw(fdf *data);


#endif //FDF_FDF_H
