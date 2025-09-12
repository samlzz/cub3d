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
FILES =	main.c \
		camera/camera_print.c \
		camera/camera_rotate.c \
		data/clear_data.c \
		data/data_init.c \
		data/game_data_init.c \
		data/install_frame_engine.c \
		data/install_hooks.c \
		data/install_mlx.c \
		data/game_camera_init/game_camera_init.c \
		data/game_camera_init/set_up_camera_dir_and_plane.c \
		lib/color.c \
		lib/str_lst.c \
		lib/vec.c \
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
		parsing/cubmap.c \
		parsing/identifiers.c \
		parsing/parse_utils.c \
		parsing/parser.c \
		parsing/update_x_dim.c \
		test/P_test_cub_parsing.c \
		test/print_cubmap.c \
		test/test_camera_rotation.c \
		test/test_get_time.c
### END ###
ifeq ($(FILES),)
    $(error FILES is empty: please define source files)
endif

# =============================================================================
#* >> USER CONFIGURATION (OPTIONAL)
# =============================================================================

AR        = ar rcs

CC        = cc
CFLAGS    = -Wall -Wextra -Werror

CXX       = c++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98

LIBFT = libft

MLX =  minilibx-linux

INCL_DIRS = $(LIBFT) $(LIBFT)/get_next_line $(SRC_DIR)lib $(MLX) $(SRC_DIR)lib/vec/ $(SRC_DIR)camera $(SRC_DIR)test $(SRC_DIR)data $(SRC_DIR)loop $(SRC_DIR)parsing $(SRC_DIR)
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

export VERBOSE    := false
export P := @
ifeq ($(VERBOSE),true)
	P :=
endif

# =============================================================================
# >> RULES
# =============================================================================

.PHONY: all
all: $(OUT)

$(OUT): $(LIBFT)/libft.a $(O_DIRS) $(OBJS)
	$(P)printf "$(GRAY)"
ifneq ($(suffix $(NAME)), .a)
	$(LD) $(LDFLAGS) $(OBJS) -o $(OUT) $(LDLIBS) $(MLX_LIB)
else
	$(LD) $(OUT) $(OBJS)
endif
	$(call clr_print,$(GREEN)$(UNDERLINE),$(NAME) compiled !)

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
