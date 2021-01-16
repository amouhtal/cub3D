/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiseparse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhtal <amouhtal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:38:57 by amouhtal          #+#    #+#             */
/*   Updated: 2020/11/26 14:39:19 by amouhtal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initial_parse(t_mlx *m)
{
	m->ccolor.r = -1;
	m->ccolor.g = -1;
	m->ccolor.b = -1;
	m->ccolor.f = -1;
	m->ccolor.c = -1;
	m->witdth = -1;
	m->height = -1;
}

char	**new_tab(void)
{
	char **tab;

	tab = (char **)malloc(sizeof(char *));
	tab[0] = NULL;
	return (tab);
}
