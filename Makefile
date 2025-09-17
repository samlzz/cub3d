# =============================================================================
#* >> USER CONFIGURATION (MANDATORY)
# =============================================================================

NAME      ?= cub3d
ifeq ($(NAME),)
    $(error NAME is empty: please define executable name)
endif

# ? Directory (end with /)
SRC_DIR   = src/
OBJ_DIR   = build/
BIN_DIR   =

### UFILES_START ###
FILES =	cubmap.c \
		main.c \
		data/camera.c \
		data/camera_init.c \
		data/data.c \
		data/install/hooks.c \
		data/install/mlx.c \
		lib/color.c \
		lib/str_lst.c \
		lib/vec/convertion_deg_rad.c \
		lib/vec/get_norm_vec.c \
		lib/vec/multiply_vec_by_scalar.c \
		lib/vec/print_vec.c \
		lib/vec/sum_vec.c \
		lib/vec/vec_rotate.c \
		loop/app_loop_hook.c \
		loop/app_update.c \
		loop/clamp_move_try_length.c \
		loop/get_time.c \
		loop/row_from_worldY.c \
		loop/try_move_and_update_pos.c \
		parsing/grid.c \
		parsing/identifiers.c \
		parsing/map_validate.c \
		parsing/parse_utils.c \
		parsing/parser.c \
		render/dda_algorithm.c \
		render/draw_clear.c \
		render/draw_vline.c \
		render/put_pixel_in_buffer.c \
		render/render_frame.c \
		test/print_cubmap.c
### END ###
ifeq ($(FILES),)
    $(error FILES is empty: please define source files)
endif

# =============================================================================
#* >> USER CONFIGURATION (OPTIONAL)
# =============================================================================

AR        = ar rcs

CC        = cc -std=gnu11
CFLAGS    = -g3 -Wall -Wextra -Werror

CXX       = c++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98

LIBFT = libft

MLX =  minilibx-linux

INCL_DIRS = $(LIBFT) $(LIBFT)/get_next_line $(MLX) $(SRC_DIR) $(SRC_DIR)lib
# ? Directories & Libraries to link against
LIB_DIRS  = $(LIBFT) $(MLX)
LIB_FILES = ft mlx Xext X11 m

RM = rm -f
MD = mkdir -p

# =============================================================================
# >> COLORS
# =============================================================================

ESC = \033[
NC = $(ESC)0;39m

GRAY = $(ESC)0;90m
RED = $(ESC)0;91m
GREEN = $(ESC)0;92m
YELLOW = $(ESC)0;93m
BLUE = $(ESC)0;94m
MAGENTA = $(ESC)0;95m
CYAN = $(ESC)0;96m
UNDERLINE = $(ESC)4m

define clr_print
	@printf "$(1)$(2)$(NC)\n"
endef

# =============================================================================
# >> AUTOMATIC VARIABLES
# =============================================================================
C_FILES   := $(filter %.c,   $(FILES))
C_SRCS    := $(addprefix $(SRC_DIR), $(C_FILES))
C_OBJS    := $(patsubst $(SRC_DIR)%.c,   $(OBJ_DIR)%.o, $(C_SRCS))

CPP_FILES  := $(filter %.cpp, $(FILES))
CPP_SRCS   := $(addprefix $(SRC_DIR), $(CPP_FILES))
CPP_OBJS   := $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(CPP_SRCS))
COMPILE.cpp = 

SRCS      := $(C_SRCS) $(CPP_SRCS)
OBJS      := $(C_OBJS) $(CPP_OBJS)
DEPS      = $(OBJS:.o=.d)
O_DIRS     = $(sort $(dir $(OBJS)))

CPPFLAGS   = $(addprefix -I, $(INCL_DIRS))
LDFLAGS    = $(addprefix -L, $(LIB_DIRS))
LDLIBS     = $(addprefix -l, $(LIB_FILES))

# ? Determin linker
ifeq ($(suffix $(NAME)), .a)
	LD = $(AR)
else ifneq ($(CPP_FILES),)
	LD = $(CXX)
else ifneq ($(C_FILES),)
	LD = $(CC)
else
	$(error Can't determine which linker to use. Please set LD manually.)
endif

OUT := $(if $(BIN_DIR),$(BIN_DIR),./)$(NAME)

export VERBOSE    ?= false
export P := @
ifeq ($(VERBOSE),true)
	P :=
endif

# =============================================================================
# >> RULES
# =============================================================================

.PHONY: all
all: $(OUT)

$(OUT): $(LIBFT)/libft.a $(MLX)/libmlx.a $(O_DIRS) $(OBJS)
	$(P)printf "$(GRAY)"
ifneq ($(suffix $(NAME)), .a)
	$(LD) $(LDFLAGS) $(OBJS) -o $(OUT) $(LDLIBS) $(MLX_LIB)
else
	$(LD) $(OUT) $(OBJS)
endif
	$(call clr_print,$(GREEN)$(UNDERLINE),$(NAME) compiled !)

$(MLX)/libmlx.a:
	make CC=clang -s -C $(MLX) 2>/dev/null

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(O_DIRS):
	$(P)$(MD) $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(P)$(CC) $(CFLAGS) -MMD $(CPPFLAGS) -c $< -o $@
	$(call clr_print, $(YELLOW),Compiling C: $<)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(P)$(CXX) $(CXXFLAGS) -MMD $(CPPFLAGS) -c $< -o $@
	$(call clr_print, $(YELLOW),Compiling C++: $<)

-include $(DEPS)

.PHONY: clean
clean:
	$(P)$(RM) $(OBJS) $(DEPS)
	$(P)$(RM) -r $(OBJ_DIR)
	$(call clr_print,$(BLUE),$(NAME) object files cleaned!)

.PHONY: fclean
fclean: clean
	$(P)$(RM) $(OUT)
	$(call clr_print,$(CYAN),executables files cleaned!)

.PHONY: re
re: fclean all

.PHONY: run
run: $(OUT)
ifneq ($(suffix $(NAME)), .a)
	$(OUT)
else
	@echo "Nothing to run for a static library: $(OUT)"
endif
