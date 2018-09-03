/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tetri.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:16:10 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/11 17:36:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static const t_tetridata g_tetridatas[] =
{
	{
		.filecode = "#*...#*...#*...#",
		.code = "BBB"
	},
	{
		.filecode = "#*...#*...##",
		.code = "BBD"
	},
	{
		.filecode = "#*...###",
		.code = "BDD"
	},
	{
		.filecode = "##*..#*...#",
		.code = "DGBB"
	},
	{
		.filecode = "###*.#",
		.code = "BHDD"
	},
	{
		.filecode = "#*...#*..##",
		.code = "BBG"
	},
	{
		.filecode = "#*.###",
		.code = "BGG"
	},
	{
		.filecode = "####",
		.code = "DDD"
	},
	{
		.filecode = "##*...#*...#",
		.code = "DBB"
	},
	{
		.filecode = "###*...#",
		.code = "DDB"
	},
	{
		.filecode = "##*...##",
		.code = "DBD"
	},
	{
		.filecode = "##*.##",
		.code = "DGBG"
	},
	{
		.filecode = "#*..##*..#",
		.code = "BGB"
	},
	{
		.filecode = "#*...##*...#",
		.code = "BDB"
	},
	{
		.filecode = "#*...##*..#",
		.code = "BDGB"
	},
	{
		.filecode = "#*..##*...#",
		.code = "BGDB"
	},
	{
		.filecode = "#*..###",
		.code = "BGDD"
	},
	{
		.filecode = "###*..#",
		.code = "DDGB"
	},
	{
		.filecode = "##*..##",
		.code = "DBG"
	}
};

/*
** Un genre de strcmp. Verifie que le code de tetri passe dans buff
** commencant a l'index 'start' est valide. Saute les '\n'.
*/

static char	*detect_tetri(char *buff, int start, t_tetridata tetri)
{
	char	endl_ok;
	char	*filecode_ptr;

	buff += start;
	endl_ok = 1;
	filecode_ptr = tetri.filecode;
	while (*filecode_ptr)
	{
		if (*filecode_ptr == '*')
		{
			endl_ok = 1;
			++filecode_ptr;
			continue ;
		}
		if (endl_ok && *buff == '\n')
		{
			++buff;
			continue ;
		}
		if (*filecode_ptr == '#')
			endl_ok = 0;
		if (*(filecode_ptr++) != *(buff++))
			return (NULL);
	}
	return (ft_strdup(tetri.code));
}

/*
** Compare le tetrimino trouve avec ceux possibles.
** Renvoie le code du tetrimino trouve avec celui possible
** NULL = error
**
** 19 = nombre de tetridatas (var globale)
*/

static char	*compare_code(int start, char *buff)
{
	char	*ret;
	int		i;

	i = 0;
	while (i < 19)
	{
		if ((ret = detect_tetri(buff, start, g_tetridatas[i])))
			return (ret);
		++i;
	}
	return (NULL);
}

/*
** Return the pos of the 1st # in the buffer.
** -1 = error.
*/

static int	find_start(char *buff)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		if (buff[i] == '#')
			return (i);
		else if (buff[i] != '.' && (buff[i] != '\n' ||
					(i != 4 && i != 9 && i != 14 && i != 19)))
			return (-1);
		++i;
	}
	return (-1);
}

/*
** Return the pos of the 4th (hopefully last) # in the buffer.
** -1 = error.
*/

static int	find_end(char *buff, int start)
{
	int	i;
	int	count;
	int	end;

	i = start;
	count = 0;
	end = -1;
	while (i < 20)
	{
		if (buff[i] == '#')
		{
			++count;
			if (count > 4)
				return (-1);
			if (count == 4)
				end = i;
		}
		else if (buff[i] != '.' && (buff[i] != '\n' ||
					(i != 4 && i != 9 && i != 14 && i != 19)))
			return (-1);
		++i;
	}
	return (end);
}

/*
** If the tetri in buff is valid, returns his code.
** buff is expected to be of size 20.
*/

char		*check_tetri(char *buff)
{
	int	start;
	int	end;

	start = -2;
	end = -2;
	if (buff[4] != '\n'
			|| buff[9] != '\n'
			|| buff[14] != '\n'
			|| buff[19] != '\n'
			|| (start = find_start(buff)) == -1
			|| (end = find_end(buff, start)) == -1)
		return (NULL);
	return (compare_code(start, buff));
}
