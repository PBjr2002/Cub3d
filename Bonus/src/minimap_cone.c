/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adimas-d <adimas-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:33:11 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/08 18:03:39 by adimas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	calculate_cone(t_data *data)
{
	t_vars	vars;

	vars_init(&vars);
	vars.x = 0;
	while (vars.x < data->width)
	{
		set_ray_dir_and_dist(data, &vars);
		set_ray_side_dist(data, &vars);
		dist_to_wall(data, &vars);
		if (vars.side == 0)
			vars.wall_dist = (vars.map_x - data->plr.pos.x \
				+ (1 - vars.step_x) / 2) / vars.ray_dir_x;
		else
			vars.wall_dist = (vars.map_y - data->plr.pos.y \
				+ (1 - vars.step_y) / 2) / vars.ray_dir_y;
		print_cone(data, &vars);
		vars.x++;
	}
}

void	print_cone(t_data *data, t_vars *vars)
{
	t_vector	screen_pos;
	int			step;
	int			scaler;

	scaler = ft_map_step(data);
	step = vars->wall_dist * scaler;
	screen_pos.x = 7 * scaler;
	screen_pos.y = 7 * scaler + (scaler / 2);
	if (step > 5 * scaler)
		step = 5 * scaler;
	while (step >= 0)
	{
		if (get_pixel_img(&data->img, screen_pos.x, screen_pos.y) == 0)
			my_mlx_pixel_put(data, screen_pos.x, screen_pos.y, 0xFF0000);
		screen_pos.x += vars->ray_dir_x;
		screen_pos.y += vars->ray_dir_y;
		step--;
	}
	if (get_pixel_img(&data->img, screen_pos.x, screen_pos.y) == 0)
		my_mlx_pixel_put(data, screen_pos.x, screen_pos.y, 0xFF0000);
}

void	dist_to_wall(t_data *data, t_vars *vars)
{
	int	i;

	i = 0;
	while (i <= 9)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (check_if_door(data, vars, 1) == 1)
			break ;
		i++;
	}
}
