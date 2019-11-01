/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <bjasper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:20:01 by bjasper           #+#    #+#             */
/*   Updated: 2019/11/01 17:13:26 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "/Users/bjasper/fillit/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define BUFF_SIZE 21

typedef struct s_fill
{
    char order;
    int x_len;
    int y_len;
    char yx[4][4];
}            t_fill;
#endif