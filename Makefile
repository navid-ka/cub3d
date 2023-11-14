NAME = $(BINDIR)/cub3D
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
SRCDIR = src
OBJDIR = obj
BINDIR = bin
UNAME  = $(shell uname)
HEADERS = include/cub3d.h
SRC = src/main.c
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
COLOR_RESET = $(shell tput sgr0)
COLOR = $(shell tput setaf 2)
KAOMOJI_SUCCESS = (づ ᴗ _ᴗ)づ♡
KAOMOJI_REMOVE = (ノಠ益ಠ)ノ彡┻━┻
LIBFT = include/libft/bin/libft.a

ifeq ($(UNAME), Darwin)
MLXDIR = include/mlx/
OLD_MAKE = /usr/bin/make3.81 #make
MLX = $(MLXDIR)libmlx.a
else
MLXDIR = include/mlx_linux/
OLD_MAKE = make
MLX = $(MLXDIR)libmlx.a
endif

all: 
	@$(MAKE) -sC include/libft
	@$(OLD_MAKE) -sC $(MLXDIR)
	@$(MAKE) ${NAME} --no-print-directory
ifeq ($(UNAME), Darwin)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(COLOR)\rCompiling (╮°-°)╮┳━┳ : $(COLOR_RESET)$<"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -c $< -o $@ -Iinclude/libft/include -I$(MLXDIR)

${NAME}: ${OBJECTS} ${HEADERS} Makefile ${LIBFT} ${MLX}
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -o ${NAME} ${OBJECTS} -Iinclude/libft/include -Linclude/libft/bin -lft \
	-I$(MLXDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
	@printf "\n$(COLOR)$(KAOMOJI_SUCCESS) Successfully compiled!$(COLOR_RESET)"
else
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(COLOR)\rCompiling (╮°-°)╮┳━┳ : $(COLOR_RESET)$<"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -03 -c $< -o $@ -Iinclude/libft/include -I$(MLXDIR)

${NAME}: ${OBJECTS} ${HEADERS} Makefile ${LIBFT} ${MLX}
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -o ${NAME} ${OBJECTS} -Iinclude/libft/include -Linclude/libft/bin -lft \
	-I$(MLXDIR) -L$(MLXDIR) -Imlx_linux -lXext -lX11 -lm -lz AppKit
	@printf "\n$(COLOR)$(KAOMOJI_SUCCESS) Successfully compiled!$(COLOR_RESET)"
endif

fclean: clean
	@rm -rf ${BINDIR}
	@$(MAKE) -C include/libft fclean
	@$(MAKE) -C $(MLXDIR) clean

clean:
	@echo "$(COLOR)$(KAOMOJI_REMOVE)$(COLOR_RESET)"
	@rm -rf ${OBJDIR}

re: fclean all

norm: 
	norminette ${SRCDIR}
	norminette ${HEADERS}

.PHONY: clean all fclean re norm
