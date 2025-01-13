/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:22:12 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:46 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	ft_print_plt_cric(t_data *data)
{
	int			i;
	int			k;
	int			j;
	int			step;
	t_vector	*temp;

	step = ft_map_step(data);
	temp = data->mini_plr;
	i = 0;
	j = 180;
	while (i < 90)
	{
		k = temp[i].y;
		while (k <= temp[j].y)
			my_mlx_pixel_put(data, temp[i].x - (step / 2), k++, 0xff0000);
		i++;
		j--;
	}
}

void	paint_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap_init(data, &minimap);
	while (minimap.step.x > 0)
	{
		minimap.map_x = floor(minimap.map_pos.x);
		minimap.screen_pos.y = data->mini_plr->y - (minimap.scaler * 5);
		minimap.step.y = 12 * (W_HEIGHT / 60);
		minimap.map_pos.y = minimap.map_pos_left_up.y;
		while (minimap.step.y > 0)
		{
			minimap.map_y = floor(minimap.map_pos.y);
			minimap_draw(data, minimap);
			minimap.screen_pos.y++;
			minimap.map_pos.y += minimap.stepper;
			minimap.step.y--;
		}
		minimap.screen_pos.x++;
		minimap.map_pos.x += minimap.stepper;
		minimap.step.x--;
	}
}

void	ft_build_minimap(t_data *data)
{
	paint_minimap(data);
	calculate_cone(data);
	ft_print_plt_cric(data);
}
