/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos_from_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:12:33 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/13 18:56:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_list *get_tetriminos_from_buffer(char *buffer)
{
	unsigned short	width;
	unsigned short	height;
	unsigned int	mask;
	char	*buffer_start;
	t_list	*list;
	t_list	*list_start;
	t_tetriminos	*tetriminos;
	char	letter;

	/*
	** Detect a tetrimino
	*/
	letter = 'A';
	list = NULL;
	mask = 0;
	height = 0;
	buffer_start = buffer;
	while (*buffer)
	{
		width = 0;
		while (*buffer != '\n')
		{
			if (width > 3 || height > 3)
				buffer_error(buffer_start);
			/*
			** add a logic so that if # doesn't appears
			** exactly 4 times, this isn't a valid tetriminos
			*/
			if (*buffer == '#')
				mask |= 1 << (width + (height * 4));
			else if (*buffer != '.')
				buffer_error(buffer_start);
			width++;
			buffer++;
		}
		height++;
		buffer++;
		if (*buffer == '\n')
		{
			/*
			** logic missing: if there are too
			** much \n between patterns
			*/
			//ft_putnbr_fd(mask, 2);
			//ft_putchar_fd('\n', 2);
			tetriminos = (t_tetriminos *)malloc(sizeof(t_tetriminos));
			tetriminos->letter = letter;
			tetriminos->pattern_id = get_pattern_id(mask);
			tetriminos->position = 0;
			if (list)
			{
				list->next = ft_lstnew(tetriminos, sizeof(*tetriminos));
				list = list->next;
			}
			else
			{
				list = ft_lstnew(tetriminos, sizeof(*tetriminos));
				list_start = list;
			}
			letter++;
			mask = 0;
			height = 0;
			buffer++;
		}
	}
	tetriminos = (t_tetriminos *)malloc(sizeof(t_tetriminos));
	tetriminos->letter = letter;
	tetriminos->pattern_id = get_pattern_id(mask);
	if (list)
	{
		list->next = ft_lstnew(tetriminos, sizeof(*tetriminos));
		list = list->next;
	}

	else
		list = ft_lstnew(tetriminos, sizeof(*tetriminos));

	return (list_start);
}
