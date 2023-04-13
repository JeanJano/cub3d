OBJS_DIR = objs

SRCS	:=	$(shell find srcs/*.c -exec basename \ {} \;)
SRCS_PARSING	:=	$(shell find srcs/parsing/*.c -exec basename \ {} \;)
SRCS_UTILS	:=	$(shell find srcs/utils/*.c -exec basename \ {} \;)
SRCS_DDA_ALGORITHM	:=	$(shell find srcs/dda_algorithm/*.c -exec basename \ {} \;)
SRCS_PROJECTION	:=	$(shell find srcs/projection/*.c -exec basename \ {} \;)
SRCS_EVENT	:=	$(shell find srcs/event/*.c -exec basename \ {} \;)

OBJS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS}}
OBJS_PARSING = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_PARSING}}
OBJS_UTILS = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_UTILS}}
OBJS_DDA_ALGORITHM = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_DDA_ALGORITHM}}
OBJS_PROJECTION = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_PROJECTION}}
OBJS_EVENT = ${patsubst %.c,${OBJS_DIR}/%.o,${SRCS_EVENT}}

HEADERS = cub3d.h

LIB = ./libft/libft.a

NAME = cub3D

CC = cc

CFLAGS = -Werror -Wall -Wextra

# -- RULES -- #

${NAME}: ${LIB} ${OBJS_DIR} ${OBJS} ${OBJS_PARSING} ${OBJS_UTILS} ${OBJS_DDA_ALGORITHM} ${OBJS_PROJECTION} ${OBJS_EVENT} ${HEADERS}
	make -C mlx --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ${OBJS_PARSING} ${OBJS_UTILS} ${OBJS_DDA_ALGORITHM} ${OBJS_PROJECTION} ${OBJS_EVENT} ${LIB} -Lmlx -lmlx -lXext -lX11 -lm -lz -L/usr/local/lib -I/usr/local/include -Imlx -o ${NAME}
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

${OBJS_DIR}/%.o: srcs/parsing/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJS_DIR}/%.o: srcs/utils/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJS_DIR}/%.o: srcs/dda_algorithm/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJS_DIR}/%.o: srcs/projection/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

${OBJS_DIR}/%.o: srcs/event/%.c
	@${CC} ${CFLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}
	@echo "\033[32mclean !\033[0m"

fclean: clean
	@make fclean -sC ./libft
	@rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re