.SILENT:
NAME		=	engine

CC			=	c++

# WIN64CC		=	x86_64-w64-mingw32-g++

CFLAGS		=	-Wall -Wextra -Werror -std=c++11 -g -fsanitize=address

# WIN64FLAGS	=	-Wall -Wextra -Werror -std=c++11

RM			=	rm -rf

LIB_DIR		=	lib/

INC_DIR		=	inc/

# WIN_INC_DIR	=	$(addprefix $(LIB_DIR), win64/inc/)

SRC_DIR		=	src/

OBJ_DIR		=	temp/

# WIN_OBJ_DIR	=	win64_temp/

CLASS_DIR	=	classes/

LINKS		=	-lGL -lglfw -lGLEW

# WIN64LINKS	=	$(addprefix -L$(LIB_DIR), win64/) -lglfw3 -lopengl32 -lglew32

SRC			=	$(addprefix $(SRC_DIR),					main.cpp	\
							$(addprefix $(CLASS_DIR),	Engine.cpp	\
														ShaderApp.cpp))

OBJ_DIRS	=	$(addprefix $(OBJ_DIR), $(CLASS_DIR))

# WIN_OBJ_DIRS=	$(addprefix $(WIN_OBJ_DIR), $(CLASS_DIR))

OBJ			=	$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

# WIN_OBJ 	= 	$(SRC:$(SRC_DIR)%.cpp=$(WIN_OBJ_DIR)%.o)

GREEN		=	\033[0;32m

RED			=	\033[0;31m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ) | $(SRC)
				printf '$(HAMMER)\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(LINKS)
				make compiled

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp | $(OBJ_DIRS)
				printf '$(HAMMER)\t'
				printf "$(GREEN)Compiling $(NAME) objects... $(RED)%-33.33s\r" $(notdir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIRS):
				mkdir -p $@

# $(WIN_OBJ_DIR)%.o:	$(SRC_DIR)%.cpp | $(WIN_OBJ_DIRS)
# 				printf '$(HAMMER)\t'
# 				printf "$(GREEN)Compiling $(NAME) objects... $(RED)%-33.33s\r" $(notdir $@)
# 				$(WIN64CC) $(WIN64FLAGS) -c $< -o $@

# $(WIN_OBJ_DIRS):
# 				mkdir -p $@

# win64:			$(WIN_OBJ) | $(SRC)
# 				printf '$(HAMMER)\t$(GREEN)Compiling $(NAME)$(RESET)\n'
# 				$(WIN64CC) -shared $^ -o $(NAME).exe -I $(INC_DIR) \
# 				-I $(WIN_INC_DIR) $(WIN64LINKS)
# 				make compiled

all:			$(NAME)

clean:
				if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				$(RM) $(NAME)
				$(RM) $(NAME).exe
				printf '$(BROOM)\t\t\t$(SUS)\n'

re:				fclean all

compiled:
				printf "																\n"
				printf "$(GREEN)	$(NAME)										$(RESET)\n"
				printf "$(GREEN)                             _  _             _ $(RESET)\n"
				printf "$(GREEN)                            (_)| |           | |$(RESET)\n"
				printf "$(GREEN)  ____   ___   ____   ____   _ | |  ____   _ | |$(RESET)\n"
				printf "$(GREEN) / ___) / _ \ |    \ |  _ \ | || | / _  ) / || |$(RESET)\n"
				printf "$(GREEN)( (___ | |_| || | | || | | || || |( (/ / ( (_| |$(RESET)\n"
				printf "$(GREEN) \____) \___/ |_|_|_|| ||_/ |_||_| \____) \____|$(RESET)\n"
				printf "$(GREEN)                     |_|                        $(RESET)\n"
				printf "																\n"

run:			all
				./$(NAME)

rerun:			fclean | run

.PHONY:			all clean fclean re run rerun
