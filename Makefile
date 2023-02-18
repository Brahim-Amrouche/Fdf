SRC_FILES = ${wildcard ./src/**/*.c}  ${wildcard ./src/*.c} 

CC = @cc

INCLUDES = -I./includes -I./libft/includes 

FLAGS = -Wall -Wextra -Werror $(INCLUDES)

NAME = fdf

SRC_OBJS = ${patsubst %.c,%.o,$(SRC_FILES)}

%.o : %.c
	$(CC) $(FLAGS) -D BONUS=1 -c $^ -o $@

all : $(NAME)

./libft/libft.a :
	@make -C ./libft

$(NAME) : ./libft/libft.a $(SRC_OBJS)
	$(CC) $(FLAGS) -D BONUS=1 -lmlx  -framework OpenGL -framework AppKit $^ -o $@

clean :
	@make -C ./libft clean
	@rm -rf $(SRC_OBJS)

fclean : clean
	@make -C ./libft fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re