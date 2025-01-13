/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:25:44 by pauberna          #+#    #+#             */
/*   Updated: 2025/01/06 18:06:57 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_data(t_data *model)
{
	model->file_name = NULL;
	model->mlx_window = NULL;
	model->img.mlx_img = NULL;
	model->width = W_WIDTH;
	model->height = W_HEIGHT;
	model->column_count = 0;
	model->line_count = 0;
	model->floor = -1;
	model->ceiling = -1;
	model->timeval = ft_calloc(sizeof(t_timeval), 1);
	model->frame = 1;
	init_walls(model);
	model->mlx = NULL;
	model->og_map = NULL;
	model->map = NULL;
	model->move = true;
}

void	init_walls(t_data *model)
{
	int	i;

	model->n_wall = NULL;
	model->s_wall = NULL;
	model->e_wall = NULL;
	model->w_wall = NULL;
	model->north_text = NULL;
	model->south_text = NULL;
	model->east_text = NULL;
	model->west_text = NULL;
	i = 0;
	while (i < 6)
	{
		model->keys[i] = 0;
		i++;
	}
}

void	vars_init(t_vars *vars)
{
	vars->x = -1;
	vars->map_x = 0;
	vars->map_y = 0;
	vars->step_x = 0;
	vars->step_y = 0;
	vars->side = 0;
	vars->line_height = 0;
	vars->draw_start = 0;
	vars->draw_end = 0;
	vars->tex_x = 0;
	vars->camera_x = 0;
	vars->ray_dir_x = 0;
	vars->ray_dir_y = 0;
	vars->delta_dist_x = 0;
	vars->delta_dist_y = 0;
	vars->side_dist_x = 0;
	vars->side_dist_y = 0;
	vars->wall_dist = 0;
	vars->wall_x = 0;
	vars->pos = 0;
	vars->step = 0;
}
