/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 19:25:12 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/28 19:25:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 501

typedef struct	s_parser
{
	int		fd;		// 4
	size_t	bcount;	// 4
	char	*buffer;// 8
}				t_parser;

int		get_next_line(int const fd, char **line);
#endif
