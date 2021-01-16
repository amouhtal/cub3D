/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:51:13 by amouhtal          #+#    #+#             */
/*   Updated: 2020/12/08 11:16:31 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_sort_sprite(t_cube *cube, double spx, double spy, int count)
{
	double	dist;
	int		i;

	i = 0;
	while (i < count - 1)
	{
		spx = cube->sprits[i].sprite_x;
		spy = cube->sprits[i].sprite_y;
		dist = cube->sprits[i].dist_to_player;
		if (dist < cube->sprits[i + 1].dist_to_player)
		{
			cube->sprits[i].sprite_x = cube->sprits[i + 1].sprite_x;
			cube->sprits[i].sprite_y = cube->sprits[i + 1].sprite_y;
			cube->sprits[i].dist_to_player = cube->sprits[i + 1].dist_to_player;
			cube->sprits[i].sprite_angle = cube->sprits[i + 1].sprite_angle;
			cube->sprits[i + 1].sprite_x = spx;
			cube->sprits[i + 1].sprite_y = spy;
			cube->sprits[i + 1].dist_to_player = dist;
			i = -1;
		}
		i++;
	}
}

void	count_sprites(t_cube *cube, int i, int j)
{
	int count;

	count = 0;
	while (cube->m.s_map.map[j])
	{
		i = 0;
		while (cube->m.s_map.map[j][i])
		{
			if (cube->m.s_map.map[j][i] == '2')
			{
				cube->sprits[count].sprite_x = (i * cube->tile_size)
				+ cube->tile_size / 2;
				cube->sprits[count].sprite_y = (j * cube->tile_size)
				+ cube->tile_size / 2;
				count++;
			}
			i++;
		}
		j++;
	}
}

double	ft_diffangle(double diffangle)
{
	if (diffangle < -3.14159)
		diffangle += 2.0 * 3.14159;
	if (diffangle > 3.14159)
		diffangle -= 2.0 * 3.14159;
	return (diffangle);
}

int		sprite_visible(t_cube *cube, int sprite_indice)
{
	double vectx;
	double vecty;
	double angle;
	double diffangle;
	double opp;

	cube->sprits->hight = (cube->tile_size /
	cube->sprits[sprite_indice].dist_to_player) * cube->dest_project_plane;
	opp = cube->sprits->hight / 2;
	cube->sprits->ag = atan(opp / cube->dest_project_plane);
	vectx = (cube->sprits[sprite_indice].sprite_x) - cube->player.player_x;
	vecty = (cube->sprits[sprite_indice].sprite_y) - cube->player.player_y;
	angle = atan2(vecty, vectx);
	if (angle <= 0.)
		angle = (2 * M_PI) + angle;
	diffangle = cube->player.angle - angle;
	diffangle = ft_diffangle(diffangle);
	diffangle = fabs(diffangle);
	if (diffangle - cube->sprits->ag < ((FOV / 2) * ANGLE_TO_RAD))
		return (1);
	else
		return (0);
}

void	found_sprite_angle(t_cube *cube, int i)
{
	double	spriteangle;
	double	x;
	double	y;

	spriteangle = 0;
	x = cube->sprits[i].sprite_x - cube->player.player_x;
	y = cube->sprits[i].sprite_y - cube->player.player_y;
	spriteangle = atan2(y, x);
	if (spriteangle <= 0.)
		cube->sprits[i].sprite_angle =
			(M_PI * 2) + spriteangle;
	else
		cube->sprits[i].sprite_angle = spriteangle;
	cube->sprits[i].sprite_angle =
		normalize_angle(cube->sprits[i].sprite_angle);
}
