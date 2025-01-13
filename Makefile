CC = cc
CFLAGS = -g -Wall -Wextra -Werror -O3 #-fsanitize=address
NAME = cub3D
B_NAME = cub3D_bonus

SRC = $(addprefix Base/src/, $(SOURCES))
SOURCES =	main.c parsing.c map_constructor.c map_normalizer.c get_textures.c get_player_info.c \
			check_map.c window.c check_content.c movement.c check_move_utils.c keys.c \
			draw_texture.c raycast.c raycast_utils.c free_stuff.c init_vars.c

B_SRC = $(addprefix Bonus/src/, $(B_SOURCES))
B_SOURCES =	main.c parsing.c map_constructor.c map_normalizer.c get_textures.c get_player_info.c \
			check_map.c window.c check_content.c minimap.c movement.c check_move_utils.c \
			minimap_draw.c keys.c mouse.c draw_texture.c raycast.c raycast_utils.c \
			door.c door_states.c minimap_cone.c free_stuff.c init_vars.c

OBJS_DIR = obj
OBJECTS = $(addprefix $(OBJS_DIR)/, $(SRC:Base/src/%.c=%.o))

B_OBJS_DIR = b_obj
B_OBJECTS = $(addprefix $(B_OBJS_DIR)/, $(B_SRC:Bonus/src/%.c=%.o))

LIBFT_DIR = include/libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = include/mlx/
MLX = $(MLX_DIR)libmlx.a -lXext -lX11 -lm -lz

Color_Off='\033[0m'       # Text Reset
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan


MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}


all: $(NAME)
	@rm -f $(B_NAME)

$(NAME): $(OBJECTS) $(MLX) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(MLX) $(LIBFT)
		$(MSG1)

$(B_NAME): $(B_OBJECTS) $(MLX) $(LIBFT)
		$(CC) $(CFLAGS) $(B_OBJECTS) -o $(B_NAME) $(MLX) $(LIBFT)
		$(MSG1)

bonus: $(B_NAME)
	@rm -f $(NAME)

$(OBJS_DIR)/%.o: Base/src/%.c
	rm -rf $(B_OBJS_DIR)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJS_DIR)/%.o: Bonus/src/%.c
	rm -rf $(OBJS_DIR)
	mkdir -p $(B_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX): 
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		$(MAKE) clean -C $(MLX_DIR)
		rm -rf $(OBJS_DIR)
		rm -rf $(B_OBJS_DIR)
		$(MSG2)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		$(MAKE) clean -C $(MLX_DIR)
		rm -f $(NAME)
		rm -f $(B_NAME)
		$(MSG3)

re: fclean all

.PHONY: all clean fclean re