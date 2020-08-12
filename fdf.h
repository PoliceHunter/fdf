//
// Created by Taisha Myrcella on 8/12/20.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

#include "libft/inc/libft.h"
#include "minilibx_macos/mlx.h"

typedef struct
{
    int width;
    int height;
    int **matrix;

    void *mlx_ptr;
    void *win_ptr;
}           fdf;

void read_map(char *file_name, fdf *data);

#endif //FDF_FDF_H
