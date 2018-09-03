/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <cpaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:17 by cpaquet           #+#    #+#             */
/*   Updated: 2017/12/12 11:47:21 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

static void	add_tetri(char *code, t_tetri **tab_tetri)
{
	static char	letter = 'A';

	if (!(*tab_tetri = (t_tetri*)malloc(sizeof(t_tetri))))
		exit_error(tab_tetri, NULL);
	(*tab_tetri)->letter = letter;
	(*tab_tetri)->code = code;
	++letter;
}

static int	lect(int fd, t_tetri **tab_tetri)
{
	char	buffer[20];
	int		read_size;
	int		really_read;
	int		t;
	char	*code;

	t = 0;
	read_size = 20;
	while ((really_read = read(fd, buffer, read_size)) > 0)
	{
		if (t == 26 || really_read != read_size
				|| (read_size == 1 && buffer[0] != '\n'))
			exit_error(tab_tetri, NULL);
		if (read_size == 20)
		{
			if (!(code = check_tetri(&buffer[0])))
				exit_error(tab_tetri, NULL);
			add_tetri(code, &tab_tetri[t++]);
		}
		read_size = (read_size == 20) ? 1 : 20;
	}
	if (really_read < 0 || read_size == 20)
		exit_error(tab_tetri, NULL);
	return (t);
}

int			import(char *filename, t_tetri **tab_tetri)
{
	int fd;

	if ((fd = open_file(filename)) == -1)
		exit_error(NULL, NULL);
	return (lect(fd, tab_tetri));
}
