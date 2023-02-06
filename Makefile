OBJS_DIR = objs

SRCS	:=	$(shell find srcs/*.c -exec basename \ {} \;)

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}

HEADERS = cub3d.h

LIB = ./libft/libft.a

NAME = cub3d

CC = cc
# CFLAGS = -Werror -Wall -Wextra
CFLAGS =

# -- RULES -- #

${NAME}: ${LIB} ${OBJS_DIR} ${OBJS} ${HEADERS}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -L/usr/local/lib -I/usr/local/include -o ${NAME}
	@echo "\033[32m$ ${NAME} compiled !"
	@echo "----------------------------\033[0m"

all: ${NAME}

${LIB}:
	@make -sC ./libft

$(OBJS_DIR):
	@mkdir -p ${OBJS_DIR}
	@echo "\033[33mcompiling ${NAME}..."

${OBJS_DIR}/%.o: srcs/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}
	@echo "\033[32mclean !\033[0m"

fclean: clean
	@make fclean -sC ./libft
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re