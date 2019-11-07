/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:33:47 by bjasper           #+#    #+#             */
/*   Updated: 2019/11/07 22:37:22 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void ft_length(t_fill a)
{
    int i;

    i = 0;
    a.x_len = a.sharp[i] % 10;
    a.y_len = a.sharp[i] / 10;
    while (++i < 4)
    {
        if (a.sharp[i] % 10 > a.x_len)
            a.x_len = a.sharp[i] % 10;
        if (a.sharp[i] / 10 > a.y_len)
            a.y_len = a.sharp[i] / 10;
    }
}

void    ft_coordinates(int *a)
{
    int i;

    i = 0;
    while (i < 4)
    {
        a[i] = a[i] / 10 * 10 + a[i] % 10;
        ++i;
    }
}

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

int validity(int fd, char *buf)
{
    /*
    ** check validity of input tetrominos. If invalid - return 0.
    */
   
    int ret;
    int i;
    int tetnum;
    int connect;
    t_fill figure[26];

    tetnum = 0;    
    while((ret = read(fd, buf, BUFF_SIZE))) //read one tetramino
    {
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
                figure[tetnum].sharp[ret] = i - 1; //memorize indexes of sharps
                connect = connect + is_figure_valid(buf, i - 1);
                // printf("%d, ", sharp[ret]);
                ++ret;
            }
            else
                return (0); 
        }
        if (ret != 4 || (connect != 3 && connect != 4)) //check validity of sharp's numbers and tetramino figure
            exit(0);
        ft_upp(figure[tetnum].sharp);
        ft_coordinates(figure[tetnum].sharp);
        ft_length(figure[tetnum]);    
        ++tetnum;
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