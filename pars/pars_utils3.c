/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:15:08 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 14:58:13 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_and_check(t_mlx *m, int *ret, char *line, int fd)
{
	int gtl;

	gtl = -1;
	while (!*ret && gtl != 0)
	{
		gtl = get_next_line(fd, &line);
		*ret = ft_check_parse_file(m, line);
		free(line);
	}
}

int		ft_check_sp_or_1_line(char **tab, int compar, int compare_to)
{
	int i;

	i = 0;
	while (tab[compar][i] == '1' || tab[compar][i] == ' ')
		i++;
	if (tab[compar][i] != '\0')
		return (0);
	i = 0;
	while (tab[compar][i])
	{
		if (tab[compar][i] == ' ' && tab[compare_to][i] == '0')
			return (0);
		i++;
	}
	return (1);
}

void	mlx_init1(t_mlx *mlx, int *i, int *ret)
{
	mlx->east = NULL;
	mlx->west = NULL;
	mlx->north = NULL;
	mlx->south = NULL;
	mlx->s_path = NULL;
	mlx->witdth = 0;
	mlx->height = 0;
	mlx->floor_c = 0;
	mlx->ceil_c = 0;
	*i = 0;
	*ret = 0;
	mlx->s_map.map = new_tab();
}

int		check_exte(char *str, int xpm)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	if (xpm == 1)
	{
		if (str[len - 1] == 'm' && str[len - 2] == 'p' &&
		str[len - 3] == 'x' && str[len - 4] == '.')
			return (1);
	}
	if (xpm == 2)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' &&
		str[len - 3] == 'c' && str[len - 4] == '.')
			return (1);
	}
	return (0);
}
