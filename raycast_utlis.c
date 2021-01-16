/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:08:24 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/03 13:50:20 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	wall_hit(t_cube *cube, double vert_distance, double horz_distance)
{
	cube->ray.wall_hit_x = (vert_distance < horz_distance) ?
	cube->ray.vert_wall_hit_x : cube->ray.horz_wall_hit_x;
	cube->ray.wall_hit_y = (vert_distance < horz_distance) ?
	cube->ray.vert_wall_hit_y : cube->ray.horz_wall_hit_y;
	cube->ray.distance = (vert_distance < horz_distance) ?
	vert_distance : horz_distance;
	cube->ray.was_hit_vert = (vert_distance < horz_distance) ? 1 : 0;
	check_texture(cube);
	cube->texture.initial_txt_data =
	(int *)mlx_get_data_addr(cube->texture.initial_txt,
	&cube->bpp, &cube->size_l, &cube->endian);
}

int		count_sprit(t_cube *cube)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while (cube->m.s_map.map[i])
	{
		j = 0;
		while (cube->m.s_map.map[i][j])
		{
			if (cube->m.s_map.map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
