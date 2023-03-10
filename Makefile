SRC_FILES = ./src/helpers/hex_helpers.c  ./src/rasterisation/fdf_color_fade.c ./src/rasterisation/fdf_neon_color.c ./src/exit_fdf.c \
./src/helpers/split_util.c           ./src/init_mlx.c                     ./src/perspectives/fdf_projection.c  ./src/rasterisation/fdf_draw_line.c \
./src/perspectives/isometric_view.c  ./src/hooks/fdf_hooks_helper.c       ./src/rasterisation/fdf_pixel_put.c \
./src/perspectives/parallel_view.c   ./src/perspectives/fdf_rotation.c    ./src/helpers/utils.c                ./src/perspectives/draw_fdf.c \
./src/parsing/fdf_map_parser.c       ./src/main.c                         ./src/helpers/math.c                 ./src/parsing/parser.c 

CC = cc

HOOKS_OBJ = ./src/hooks/fdf_hooks.o

BONUS_HOOKS_OBJ = ./src/hooks/fdf_hooks_bonus.o

INCLUDES = -I./includes -I./libft/includes 

FLAGS = -Wall -Wextra -Werror $(INCLUDES)

NAME = fdf

SRC_OBJS = ${patsubst %.c,%.o,$(SRC_FILES)}

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@

all : 
	@make $(NAME) BON=FALSE

./libft/libft.a :
	@make -C ./libft
	
$(NAME) : ./libft/libft.a $(SRC_OBJS) ${HOOKS_OBJ}
	$(CC) $(FLAGS) -lmlx  -framework OpenGL -framework AppKit $^ -o $@

bonus : ./libft/libft.a ${SRC_OBJS} ${BONUS_HOOKS_OBJ}
	$(CC) $(FLAGS) -lmlx  -framework OpenGL -framework AppKit $^ -o ${NAME}

clean :
	@make -C ./libft clean
	@rm -rf $(SRC_OBJS) ${HOOKS_OBJ} ${BONUS_HOOKS_OBJ}

fclean : clean
	@make -C ./libft fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re