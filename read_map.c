//
// Created by Taisha Myrcella on 8/12/20.
//

#include "fdf.h"

int get_height(char *file_name)
{
    char *line;
    int fd;
    int height;

    fd = open(file_name, O_RDONLY, 0);
    height = 0;
    while (get_next_line(fd, &line))
    {
        height++;
        free(line);
    }
    close(fd);
    return (height);
}

int get_width(char *filename)
{
    char *line;
    int fd;
    int width;

    fd = open(filename, O_RDONLY, 0);
    get_next_line(fd, &line);
    width = count_words(line, ' ');
    free(line);
    close(fd);
    return (width);
}

void fill_matrix(int *z_line, char *line)
{
    char **nums;
    int i;
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

void read_map(char *file_name, fdf *data)
{
    int fd;
    char *line;
    int i;

    data->height = get_height(file_name);
    data->width = get_width(file_name);
    data->matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
    i = 0;
    while (i <= data->height)
        data->matrix[i++] = (int *)malloc(sizeof(int) * (data->width + 1));
    fd = open(file_name, O_RDONLY, 0);
    i = 0;
    while (get_next_line(fd, &line)) {
        fill_matrix(data->matrix[i], line);
        free(line);
        i++;
    }
    close(fd);
    data->matrix[i] = NULL;
}
