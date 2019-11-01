/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:33:47 by bjasper           #+#    #+#             */
/*   Updated: 2019/11/01 19:11:46 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void    ft_upp(int *a)
{
    /*
    ** Replace the tetramino to the upp and left position
    */

    int i;
    
    while (a[0] % 5 != 0 && a[1] % 5 != 0 && a[2] % 5 != 0 && a[3] % 5 != 0)
    {
        i = 0;
        while (i < 4)
        {
            a[i] -= 1;
            ++i;
        }
    }
    while (a[0] > 3 && a[1] > 3 && a[2] > 3 && a[3] > 3)
    {
        i = 0;
        while (i < 4)
        {
            a[i] -= 5;
            ++i;
        }
    }
}

int is_figure_valid(char *buf, int i)
{
    /*
    ** Check connections between sharps
    */

    int connect;

    connect = 0;
    if (buf[i - 1] == '#')
        ++connect;
    if (buf[i - 5] == '#')
        ++connect;
    return (connect);
}

int ft_save(int tetnum, int *sharp, t_fill figure)
{
    /* 
    ** it makes two-dimensional array of valid tetrominos 
    */
   
    int x;
    int y;
    int i;

    y = 0;
    figure.order = 'A' + tetnum;
    while (y++ < 4)
    { 
        x = 0;
        while (x++ < 4)
            figure.yx[y - 1][x - 1] = '.';
    }
    i = 0;
    while (i++ < 4)
    {
        y = sharp[i - 1] / 5;
        x = sharp[i - 1] % 5;
        figure.yx[y][x] = figure.order;
        printf("bukva %c;", figure.yx[y][x]);
    }
    figure.x_len = x + 1;
    figure.y_len = y + 1;
    printf("%d:%d\n", figure.x_len, figure.y_len);
    return (0);
}

int validity(int fd, char *buf)
{
    /*
    ** check validity of input tetrominos. If invalid - return 0.
    */
   
    int sharp[4];
    int ret;
    int i;
    int tetnum;
    int connect;
    t_fill figure[26];

    int m;

    tetnum = 0;    
    while((ret = read(fd, buf, BUFF_SIZE))) //read one tetramino
    {
        m = 0;
        connect = 0;
        i = 0;
        if (ret < 20 || (ret == 21 && buf[20] != '\n') || tetnum > 26) 
            exit(0);
        ret = 0;
        while (i < 20)  //check validity of possible simbols in tetrominos
        {
            if (buf[i] == '.' && (i + 1) % 5 != 0)
                ++i;
            else if (buf[i] == '\n' && (i + 1) % 5 == 0)
                ++i;
            else if (buf[i++] == '#' && i % 5 != 0 && ret < 4)
            {
                sharp[ret] = i - 1; //memorize indexes of sharps 
                connect = connect + is_figure_valid(buf, i - 1);
                // printf("%d, ", sharp[ret]);
                ++ret;
            }
            else
                return (0); 
        }
        if (ret != 4 || (connect != 3 && connect != 4)) //check validity of sharp's numbers and tetramino figure
            exit(0);
        printf("\n%d connections\n", connect);
        ft_upp(sharp);

        while (m < 4)
        {
            printf("%d, ", sharp[m]);
            ++m;
        }
        
        ft_save(tetnum, sharp, figure[tetnum]);
        ++tetnum;
        printf("\n");
    }
    return (tetnum);
}

int		main(int ac, char **av)
{
	int		fd;
	char	buf[BUFF_SIZE];

    fd = open(av[1], O_RDONLY);
    if (fd < 0 || ac != 2)
        exit(0);
	printf("%d", validity(fd, buf));
	return (0);
}