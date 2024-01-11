NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
SRCDIR = src
OBJDIR = obj
UNAME  = $(shell uname)
HEADERS = include/cub3d.h include/raycast.h
SRC = src/main.c \
		src/garbage_collector/garbage.c \
		src/parser/parser.c \
		src/parser/structs_init.c \
		src/parser/fd_checker.c \
		src/parser/colors.c \
		src/parser/utils.c \
		src/parser/orientations.c \
		src/parser/map_parser.c \
		src/raycast/raycast.c \
		src/raycast/raycast_utils.c \
		src/window/window.c \
		src/screen_manager/screen_manager.c \
		src/animations/sword.c \
		src/minimap/draw_minimap.c \
		src/combat/combat.c \
		src/combat/enemies_loader.c \
		src/animations/time.c \
		src/window/update_window.c \
		src/img_loader/img_load.c \
		src/img_loader/img_utils.c \
		src/img_loader/img_utils2.c \
		src/img_loader/fonts.c \
		

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
COLOR_RESET = $(shell tput sgr0)
COLOR = $(shell tput setaf 2)
KAOMOJI_SUCCESS = (づ ᴗ _ᴗ)づ♡
KAOMOJI_REMOVE = (ノಠ益ಠ)ノ彡┻━┻
LIBFT = include/libft/bin/libft.a

ifeq ($(UNAME), Darwin)
SRC += src/inputs/input.c
SRC += src/map_renderer/player.c
MLXDIR = include/mlx/
OLD_MAKE = /usr/bin/make3.81 #make
MLX = $(MLXDIR)libmlx.a
LMLX = -Iinclude/libft/include -Linclude/libft/bin -lft \
	-I$(MLXDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit
else
SRC += src/inputs/input_linux.c
MLXDIR = include/mlx_linux/
OLD_MAKE = make
MLX = $(MLXDIR)libmlx.a
LMLX = -Iinclude/libft/include -Linclude/libft/bin -lft -I$(MLXDIR) -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
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
	@gcc $(CFLAGS) ${OBJECTS} $(LMLX) -o ${NAME} 
	@printf "\n$(COLOR)$(KAOMOJI_SUCCESS) Successfully compiled!$(COLOR_RESET)"
else
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(COLOR)\rCompiling (╮°-°)╮┳━┳ : $(COLOR_RESET)$<"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -c $< -o $@ -Iinclude/libft/include -I$(MLXDIR)

${NAME}: ${OBJECTS} ${HEADERS} Makefile ${LIBFT} ${MLX}
	@mkdir -p $(@D)
	@gcc $(CFLAGS) $(SRC) $(LMLX) -o $(NAME)
	@printf "\n$(COLOR)$(KAOMOJI_SUCCESS) Successfully compiled!$(COLOR_RESET)"
endif

fclean: clean
	@rm -rf ${NAME}
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
