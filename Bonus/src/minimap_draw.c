/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:55:59 by adimas-d          #+#    #+#             */
/*   Updated: 2025/01/06 18:04:37 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

float	ft_map_step(t_data *data)
{
	float	step_x;
	float	step_y;

	step_x = data->width / 60;
	step_y = data->height / 60;
	if (step_x > step_y)
		return (step_y);
	else
		return (step_x);
}

void	minimap_init(t_data *data, t_minimap *minimap)
{
	minimap->scaler = ft_map_step(data);
	minimap->map_pos_left_up.x = data->plr.pos.x - 5;
	minimap->map_pos_left_up.y = data->plr.pos.y - 5;
	minimap->map_pos_right_down.x = data->plr.pos.x + 6;
	minimap->map_pos_right_down.y = data->plr.pos.y + 6;
	minimap->screen_pos.x = data->mini_plr->x - (minimap->scaler * 5);
	minimap->step.x = 12 * (W_WIDTH / 60);
	minimap->map_pos.x = minimap->map_pos_left_up.x;
	minimap->stepper = 1 / (float)minimap->scaler;
}

void	minimap_draw(t_data *data, t_minimap m_map)
{
	if (m_map.map_y < 0 || m_map.map_x < 0 || m_map.map_y >= data->line_count \
		|| m_map.map_x >= data->column_count)
		my_mlx_pixel_put(data, m_map.screen_pos.x, \
			m_map.screen_pos.y, 0x808080);
	else if (data->map[m_map.map_y][m_map.map_x] == '1')
		my_mlx_pixel_put(data, m_map.screen_pos.x, \
			m_map.screen_pos.y, 0x3399ff);
	else if (data->map[m_map.map_y][m_map.map_x] == ' ')
		my_mlx_pixel_put(data, m_map.screen_pos.x, \
			m_map.screen_pos.y, 0x808080);
	else if (data->map[m_map.map_y][m_map.map_x] == 'D')
	{
		m_map.door_nb = find_door_num(data, m_map.map_x, m_map.map_y);
		if (m_map.door_nb >= 0 && data->door[m_map.door_nb].open == 0)
			my_mlx_pixel_put(data, m_map.screen_pos.x, \
				m_map.screen_pos.y, 0xFFCC66);
		else
			my_mlx_pixel_put(data, m_map.screen_pos.x, \
				m_map.screen_pos.y, 0x000000);
	}
	else
		my_mlx_pixel_put(data, m_map.screen_pos.x, \
			m_map.screen_pos.y, 0x000000);
}
