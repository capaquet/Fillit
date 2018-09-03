/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 14:15:16 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/08 15:06:12 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_grid(t_grid *grid)
{
	int i;

	i = 0;
	while (i < GRID_SIZE)
	{
		ft_putchar(grid->array[i]);
		if (i != 0 && ((i + 1) % GRID_SIDE) == 0)
			ft_putchar('\n');
		++i;
	}
}

/*
** Print only the best square containing all the tetri.
*/

void	print_result(t_grid *grid)
{
	int i;
	int	y;

	i = 0;
	y = 0;
	while (y < grid->square_side && i < GRID_SIZE)
	{
		ft_putchar(grid->array[i]);
		if (i != 0 && (i - (y * GRID_SIDE) == grid->square_side - 1))
		{
			ft_putchar('\n');
			++y;
			i += GRID_SIDE - grid->square_side;
		}
		++i;
	}
}
