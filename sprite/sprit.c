/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:19 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/08 10:50:27 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	drow_strips(t_cube *cube, int s_x, int i, int x)
{
	int y;
	int xtext;
	int ytext;
	int start;

	start = -1;
	y = 0;
	start = (cube->m.height / 2) - (cube->sprits->hight / 2);
	if (start < 0)
	{
		y = -start;
		start = -1;
	}
	xtext = x * ((double)TEXTURE_DEM / (double)cube->sprits->hight);
	if (cube->end > (int)cube->m.height)
		cube->end = (int)cube->m.height;
	while (++start < cube->end)
	{
		ytext = y * ((double)TEXTURE_DEM / (double)cube->sprits->hight);
		cube->sprits->color = cube->txt_sprit_data[ytext * TEXTURE_DEM + xtext];
		if (cube->ray.dist_tab[s_x] > cube->sprits[i].dist_to_player)
			if (cube->sprits->color != 0x00000)
				cube->data[start * cube->m.witdth + s_x] = cube->sprits->color;
		y++;
	}
}

void	drowsprite(t_cube *cube, int i)
{
	int x;
	int y;

	y = 0;
	x = 0;
	cube->sprits[i].dist_to_player = cube->sprits[i].dist_to_player
	* cos(cube->ray.angle - cube->player.angle);
	cube->sprits->hight = (cube->tile_size /
	cube->sprits[i].dist_to_player) * cube->dest_project_plane;
	cube->end = (cube->m.height / 2) + (cube->sprits->hight / 2);
	cube->sprits->x_star_wind = (tan((FOV * ANGLE_TO_RAD) / 2)
	* cube->dest_project_plane) + (tan(cube->sprits[i].sprite_angle
	- cube->player.angle) * cube->dest_project_plane)
	- (cube->sprits->hight / 2);
	while (x < cube->sprits->hight)
	{
		if (cube->sprits->x_star_wind >= 0 &&
		cube->sprits->x_star_wind < (int)cube->m.witdth)
			drow_strips(cube, cube->sprits->x_star_wind, i, x);
		x++;
		cube->sprits->x_star_wind++;
	}
}

void	draw_sprite(t_cube *cube, int count)
{
	int i;

	i = 0;
	cube->player.angle = normalize_angle(cube->player.angle);
	while (i < count)
	{
		found_sprite_angle(cube, i);
		if (sprite_visible(cube, i) == 1)
			drowsprite(cube, i);
		i++;
	}
}

void	find_sprits(t_cube *cube)
{
	int count;

	count = 0;
	while (count < cube->nbrofsprites)
	{
		cube->sprits[count].dist_to_player =
		distance_btw_point(cube->sprits[count].sprite_x,
		cube->sprits[count].sprite_y, cube->player.player_x,
		cube->player.player_y);
		count++;
	}
	ft_sort_sprite(cube, 0, 0, count);
	draw_sprite(cube, count);
}
