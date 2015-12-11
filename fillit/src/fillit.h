/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 21:06:30 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/10 21:06:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>

/*
** Since we know all the possible patterns, we can set a pattern
** map and pull from this map whenever a tetrimino is needed
** according to an id.
*/
typedef struct		s_tetriminos
{
	char	letter;
	char	pattern_id;
}			t_tetriminos;

char	*read_tetri_file(char *);
void	get_tetriminos_from_buffer(char *);
void	buffer_error(char *);
void	error(void);

extern char *g_pattern_table[18][5];

#endif
