/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loswaldo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:49:50 by loswaldo          #+#    #+#             */
/*   Updated: 2021/03/12 01:49:53 by loswaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	swap(double *d1, double *d2)
{
	double tmp;

	tmp = *d2;
	*d2 = *d1;
	*d1 = tmp;
}

void	swap_value(t_sprites *first, t_sprites *second)
{
	swap(&first->dist, &second->dist);
	swap(&first->x, &second->x);
	swap(&first->y, &second->y);
}

void	sprite_sorting(t_config *config, t_sprites *sp)
{
	int i;
	int j;

	i = 0;
	while (i < config->sp_quantity)
	{
		sp[i].dist = ((config->pl_pos_x - sp[i].x) *
			(config->pl_pos_x - sp[i].x) + (config->pl_pos_y - sp[i].y)
			* (config->pl_pos_y - sp[i].y));
		i++;
	}
	i = 0;
	while (i < config->sp_quantity)
	{
		j = config->sp_quantity - 1;
		while (j > i)
		{
			if (sp[j - 1].dist < sp[j].dist)
			{
				swap_value(&sp[j - 1], &sp[j]);
			}
			j--;
		}
		i++;
	}
}
