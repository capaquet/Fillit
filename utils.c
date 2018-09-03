/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:22:17 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/12 11:47:46 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Print 'error' then exit with EXIT_FAILURE.
*/

void		exit_error(t_tetri **tab_tetri, t_grid *grid)
{
	int i;

	i = 0;
	while (tab_tetri && tab_tetri[i] != NULL)
	{
		free(tab_tetri[i]->code);
		free(tab_tetri[i]);
		i++;
	}
	if (grid)
	{
		if (grid->array)
			free(grid->array);
		free(grid);
	}
	free(grid);
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

/*
** Print the usage of the then exit with EXIT_SUCCESS.
*/

void		exit_usage(void)
{
	ft_putendl("usage: ./fillit <input_file>");
	exit(EXIT_SUCCESS);
}

/*
** Compute the minimal square side size for nb_tetri.
*/

static int	min_square(int nb_tetri)
{
	int square_side;

	square_side = nb_tetri * 4;
	while (ft_sqrt(square_side) == 0)
		square_side++;
	return (ft_sqrt(square_side));
}

/*
** Create a grid and intitialize it with an optimized minimal
** square size depending on the parameter nb_tetri.
** The parameter grid_size is the wanted size of the grid.
** grid_size of 9 creates a 3*3 grid.
*/

t_grid		*init_grid(int nb_tetri)
{
	t_grid	*grid;
	int		i;
	int		y;

	if (!(grid = (t_grid*)malloc(sizeof(t_grid)))
			|| !(grid->array = (char*)malloc(GRID_SIZE)))
		exit_error(NULL, grid);
	grid->square_side = min_square(nb_tetri);
	i = 0;
	y = 0;
	while (i < GRID_SIZE)
	{
		if (y > grid->square_side - 1
				|| (i - (y * GRID_SIDE)) >= grid->square_side)
			grid->array[i] = BLOCKED_CHAR;
		else
			grid->array[i] = EMPTY_CHAR;
		if (i != 0 && (i - (y * GRID_SIDE) == GRID_SIDE - 1))
			++y;
		++i;
	}
	return (grid);
}

/*
** Clear the square and widen it by 1.
*/

void		widen_square(t_grid *grid)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (y <= grid->square_side)
	{
		grid->array[i] = EMPTY_CHAR;
		if (i != 0 && (i - (y * GRID_SIDE) == grid->square_side))
		{
			++y;
			i += GRID_SIDE - grid->square_side - 1;
		}
		++i;
	}
	grid->square_side++;
}
