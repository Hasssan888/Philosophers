CC = cc 

FLAGC = -Wall -Wextra -Werror -g3 -fsanitize=thread

NAME = philo


SRC = philo_utilis.c philo.c init_data.c monitor.c routine.c utils.c


OBJE = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJE}
	${CC} ${FLAGC} -o ${NAME} ${OBJE}


%.o: %.c
	${CC} ${FLAGC} -c $< -o $@

clean :
	rm -f ${OBJE}

fclean : clean
	rm -f $(NAME)

re: fclean all