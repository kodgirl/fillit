/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjasper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:43:50 by bjasper           #+#    #+#             */
/*   Updated: 2019/10/10 17:21:57 by bjasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *begin_list)
{
	t_list	*pointer;
	int		i;

	i = 0;
	pointer = begin_list;
	while (pointer)
	{
		i++;
		pointer = pointer->next;
	}
	return (i);
}
