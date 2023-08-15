SRCS			= philo.c\
				  ft_help.c\
				  ft_help_philo.c\
				  ft_check.c

CC				= clang
RM				= rm -f
FLAGS			= #-g3
CFLAG			= #-fsanitize=thread -g3 #-Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAG) $(OBJS) -o $(NAME) $(FLAGS)

.c.o: $(SRCS)
	$(CC) $(CLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)
