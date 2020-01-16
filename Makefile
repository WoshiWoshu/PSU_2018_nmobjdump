##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CC		=       gcc

RM		=	rm -f

INCDIRS		=	$(addprefix -I, $(shell find ./include -type d -print))

CFLAGS		=        -Wall -Wextra -Wmissing-prototypes

CPPFLAGS	+=       $(INCDIRS)

OBJDUMP		=	my_objdump

NM		=	my_nm

SRCS		=	./obj/conduct_projection.c	\
			./obj/print_arch_sixty_four.c	\
			./obj/print_arch_thirty_two.c	\
			./obj/my_objdump.c		\
			./print_ascii.c			\
			./obj/main.c

SRCS2		=	./obj/conduct_projection.c	\
			./nm/main.c

OBJS            =       $(SRCS:.c=.o)

OBJS2           =       $(SRCS2:.c=.o)

all             :       $(OBJDUMP) $(NM)

nm		:	$(NM)

objdump		:	$(OBJDUMP)

$(OBJDUMP)      :       $(OBJS)
		$(CC) -o $(OBJDUMP) $(OBJS)

$(NM)		:	$(OBJS2)
		$(CC) -o $(NM) $(OBJS2)

clean           :
		$(RM) $(OBJS) $(OBJS2)

fclean          :       clean
			$(RM) $(OBJDUMP) $(NM)

re              :       fclean all

.PHONY		:	all clean fclean re
