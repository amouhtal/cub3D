/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:11:09 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/08 11:19:25 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_draw_sky(t_cube *cube, int wall_strip_heigh, int x_start)
{
	int end;
	int start;

	start = 0;
	end = ((int)cube->m.height / 2) - wall_strip_heigh / 2;
	while (start <= end)
	{
		if (start * cube->m.witdth + x_start < cube->m.witdth * cube->m.height)
			cube->data[start * cube->m.witdth + x_start] = cube->m.ceil_c;
		start++;
	}
}

void	ft_draw_floor(t_cube *cube, int x_start, int wall_strip_heigh)
{
	int start;
	int end;

	start = (cube->m.height / 2) + wall_strip_heigh / 2;
	end = cube->m.height;
	while (start < end)
	{
		if (start * cube->m.witdth + x_start < cube->m.witdth * cube->m.height)
			cube->data[start * cube->m.witdth + x_start] = cube->m.floor_c;
		start++;
	}
}

void	ft_draw_wall(t_cube *cube,
int x_start, int wall_strip_heigh, int hit)
{
	int i;
	int y;
	int x;
	int k;

	i = 0;
	cube->end = (cube->m.height / 2) + (wall_strip_heigh / 2);
	if (cube->end > (int)cube->m.height)
		cube->end = (int)cube->m.height;
	if (cube->start < 0)
	{
		i -= cube->start;
		cube->start = 0;
	}
	while (cube->start < cube->end)
	{
		y = (i * TEXTURE_DEM) / wall_strip_heigh;
		x = (int)fmod((int)hit, cube->tile_size);
		k = cube->start * cube->m.witdth + x_start;
		cube->data[k] = cube->texture.initial_txt_data[y * TEXTURE_DEM + x];
		i++;
		cube->start++;
	}
}

void	fill_image(t_cube *cube, int x_start, int wall_strip_heigh, int hit)
{
	int start;
	int end;

	start = (cube->m.height / 2) - (wall_strip_heigh / 2);
	end = (cube->m.height / 2) + (wall_strip_heigh / 2);
	cube->start = (cube->m.height / 2) - (wall_strip_heigh / 2);
	ft_draw_wall(cube, x_start, wall_strip_heigh, hit);
	ft_draw_sky(cube, wall_strip_heigh, x_start);
	ft_draw_floor(cube, x_start, wall_strip_heigh);
}
