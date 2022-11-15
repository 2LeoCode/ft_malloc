ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).a
SLINK=libft_malloc.a

CC=gcc
CFLAGS=-Wall -Wextra -Werror -MMD
AR=ar rcs
RM=rm -f

SRCDIR=src
SRC=malloc.c free.c malloc_int.c show_alloc_mem.c init_locks.c realloc.c
SRC:=$(addprefix $(SRCDIR)/, $(SRC))

OBJDIR=obj
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

DEP=$(OBJ:.o=.d)

all: $(NAME) Makefile

-include $(DEP)

$(NAME): $(OBJ)
	$(AR) $@ $^
	ln -sf $@ $(SLINK)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME) $(SLINK)

re: fclean all

.PHONY: all clean fclean re
