# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntitan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 15:17:55 by ntitan            #+#    #+#              #
#    Updated: 2022/07/24 15:00:10 by ntitan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
NAME		=	philo
CFLAGS		=	-Wall -Wextra
COPTIONS	=	-O3 -ffast-math #-fsanitize=thread -fPIE -g
RM			=	rm -f
LIBRARY		=	
INCLUDE_DIR	=	inc
OBJS_DIR	=	objects
# ------------------------------------------------------------------------------
SRCS		=	\
				ft_atoi	\
				main	\
				pthread	\
				utils	\
				utils1	\
				utils2
# ------------------------------------------------------------------------------
HDRS		=	\
				philo	\
# ------------------------------------------------------------------------------
OBJS		=	$(addprefix ${OBJS_DIR}/,${SRCS:=.o})
DEPS		=	$(addprefix ${INCLUDE_DIR}/,${HDRS:=.h})
INCLUDE		=	$(addprefix -I ,${DEPS})
LIBRARY		=	-pthread
LIBFT		=	

# ------------------------------------------------------------------------------
${OBJS_DIR}/%.o: %.c ${DEPS}
	${CC}		${CFLAGS}  ${COPTIONS} -c -o $@ $< ${INCLUDE}

# ------------------------------------------------------------------------------
$(NAME):		${OBJS_DIR} ${OBJS} ${DEPS} Makefile
	${CC}		-o ${NAME} ${CFLAGS} ${COPTIONS} ${OBJS} ${LIBRARY} ${LIBFT}

all:
	${MAKE}		${NAME}	-j

# ------------------------------------------------------------------------------
clean:
	${RM}		${OBJS}

# ------------------------------------------------------------------------------
fclean:			clean
	${RM}		${NAME}

# ------------------------------------------------------------------------------
${OBJS_DIR}:
	mkdir		-p ${OBJS_DIR}

# ------------------------------------------------------------------------------
re:				fclean all

# ------------------------------------------------------------------------------
.PHONY:			all clean fclean re
