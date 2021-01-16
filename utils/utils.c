/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:56:16 by amouhtal          #+#    #+#             */
/*   Updated: 2020/11/28 12:56:40 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

double	distance_btw_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	normalize_angle(double angle)
{
	if (angle > (2. * M_PI))
		angle -= (2. * M_PI);
	if (angle < 0.)
		angle += (2. * M_PI);
	return (angle);
}

char	hass_walll(int x, int y, t_cube *cube)
{
	int mapx;
	int mapy;

	mapx = x / cube->tile_size;
	mapy = y / cube->tile_size;
	return (cube->m.s_map.map[mapy][mapx]);
}

void	find_player(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cube->m.s_map.map[j])
	{
		i = 0;
		while (cube->m.s_map.map[j][i])
		{
			if (cube->m.s_map.map[j][i] == '5')
			{
				cube->player.player_x = (i * cube->tile_size)
				+ (cube->tile_size / 2);
				cube->player.player_y = (j * cube->tile_size)
				+ (cube->tile_size / 2);
			}
			i++;
		}
		j++;
	}
}

void	is_facing_what(t_cube *cube)
{
	cube->ray.isfaycingup = 0;
	cube->ray.isfaycingdown = 0;
	cube->ray.isfaycingright = 0;
	cube->ray.isfaycingleft = 0;
	if (cube->ray.angle > 0 && cube->ray.angle < M_PI)
		cube->ray.isfaycingdown = 1;
	else
		cube->ray.isfaycingup = 1;
	if (cube->ray.angle < (3 * M_PI) / 2 && cube->ray.angle > M_PI / 2)
		cube->ray.isfaycingleft = 1;
	else
		cube->ray.isfaycingright = 1;
}
