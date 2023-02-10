LIBFT_SRCS = ft_atoi.c   ft_isalpha.c      ft_itoa.c        ft_memcpy.c       ft_putendl_fd.c   ft_strchr.c       ft_strlcat.c      ft_strncmp.c      ft_substr.c ft_bzero.c   ft_isascii.c  ft_memmove.c  ft_putnbr_fd.c   ft_strdup.c       ft_strlcpy.c      ft_strnstr.c      ft_tolower.c    ft_calloc.c  ft_isdigit.c      ft_memchr.c       ft_memset.c       ft_putstr_fd.c    ft_striteri.c     ft_strlen.c       ft_strrchr.c      ft_toupper.c ft_isalnum.c   ft_isprint.c         ft_memcmp.c       ft_putchar_fd.c   ft_split.c        ft_strjoin.c      ft_strmapi.c      ft_strtrim.c

LIBFT_BONUS = ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c

PRINTF_SRCS = ./ft_printf/ft_printf.c \
    ./ft_printf/ft_converters_utils.c \
	./ft_printf/ft_flags_parser.c \
	./ft_printf/ft_converters_1.c \
	./ft_printf/ft_flags_applier.c

GNL_SRCS = ./gnl/get_next_line_utils_bonus.c \
	./gnl/get_next_line_bonus.c

GCG_SRCS = ${wildcard ./ft_garbage_collector/*.c}

INCLUDES = -I./includes

FLAGS = -Wall -Wextra -Werror $(INCLUDES)

GCC = cc

NAME = libft.a

LIBFT_OBJS = ${patsubst %.c,%.o,$(LIBFT_SRCS)}

LIBFT_B_OBJS = ${patsubst %.c,%.o,$(LIBFT_BONUS)}

PRINTF_OBJS = ${patsubst %.c,%.o,$(PRINTF_SRCS)}

GNL_OBJS = ${patsubst %.c,%.o,$(GNL_SRCS)}

CGC_OBJS = ${patsubst %.c,%.o,$(GCG_SRCS)}

OBJS = $(LIBFT_OBJS) $(LIBFT_B_OBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(CGC_OBJS)

%.o : %.c
	@${GCC} ${FLAGS} -c $^ -o $@

all : ${NAME}

${NAME} :  ${OBJS}
	ar -rcs $@ ${OBJS}

clean :
	@rm -f ${OBJS} 

fclean : clean
	@rm -f ${NAME}

re : fclean	all

.PHONY : all clean fclean re