/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:36:55 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/09 15:00:24 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		bypass_space(char *str, int *i)
{
	int ret;

	while (str[*i] == ' ')
		(*i)++;
	return (ret = *i);
}

int		ft_ceil(t_mlx *m, char *line, int i)
{
	m->ccolor.r = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[bypass_space(line, &i)] == ',' && i > 2)
		i++;
	else
		return (2);
	m->ccolor.g = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[bypass_space(line, &i)] == ',' && line[i - 1] != ',')
		i++;
	else
		return (2);
	m->ccolor.b = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i - 1] == ',')
		return (2);
	if (line[bypass_space(line, &i)] != '\0' || m->ccolor.r > 255
		|| m->ccolor.g > 255 || m->ccolor.b > 255)
		return (2);
	m->ccolor.c = 1;
	m->ceil_c = m->ccolor.r * 256 * 256 + m->ccolor.g * 256 + m->ccolor.b;
	return (0);
}

int		ft_floor(t_mlx *m, char *line, int i)
{
	m->ccolor.r = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i = bypass_space(line, &i)] == ',' && i > 2)
		i++;
	else
		return (2);
	m->ccolor.g = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[bypass_space(line, &i)] == ',' && line[i - 1] != ',')
		i++;
	else
		return (2);
	m->ccolor.b = ft_atoi2(&line[bypass_space(line, &i)]);
	while ((line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i - 1] == ',')
		return (2);
	if (line[bypass_space(line, &i)] != '\0' || m->ccolor.r > 255
		|| m->ccolor.g > 255 || m->ccolor.b > 255)
		return (2);
	m->ccolor.f = 1;
	m->floor_c = m->ccolor.r * 256 * 256 + m->ccolor.g * 256 + m->ccolor.b;
	return (0);
}

void	check_color_resolution(t_mlx *m, int *ret)
{
	if (((int)m->witdth <= 0 || (int)m->height <= 0) && *ret == 0)
		*ret = 1;
	else if ((m->ccolor.c != 1 || m->ccolor.f != 1) &&
	*ret != 4 && *ret != 1 && *ret != 2)
		*ret = 2;
	else if (m->s_map.map[0] == NULL && *ret != 4 && *ret != 1 && *ret != 2)
		*ret = 3;
	if (*ret == 1)
		write(1, "Error\nResolution Error", 22);
	else if (*ret == 2)
		write(1, "Error\nFloor or ceil Error", 25);
	else if (*ret == 3)
		write(1, "Error\nCheck Map", 15);
	else if (*ret == 4)
		write(1, "Error\nInvalid elements", 22);
	if (*ret != 0)
		exit(0);
}

int		ft_res(t_mlx *mlx, char *line)
{
	int i;

	i = 2;
	if (mlx->height || mlx->witdth)
		return (4);
	while (line[i] == ' ')
		i++;
	mlx->witdth = ft_atoi(&line[i]);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	mlx->height = ft_atoi(&line[i]);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	if (mlx->witdth > 2560)
		mlx->witdth = 2560;
	if (mlx->height > 1440)
		mlx->height = 1440;
	if (mlx->height <= 0 || mlx->witdth <= 0 || line[i])
		return (1);
	return (0);
}
