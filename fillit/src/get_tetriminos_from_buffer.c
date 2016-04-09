/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos_from_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:12:33 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/16 11:59:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** TODO: free all the mallocs and ft_lstnew !!
*/
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
	list_start = NULL;
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
			** TODO: check if there is more than one \n between patterns
			*/
			tetriminos = (t_tetriminos *)malloc(sizeof(t_tetriminos));
			tetriminos->letter = letter;
			tetriminos->pattern_id = get_pattern_id(mask);
			tetriminos->h_shift = 0;
			tetriminos->v_shift = 0;
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

	if (!list_start)
		list_start = list;

	return (list_start);
}
