.SILENT:
NAME		=	engine

CC			=	c++

CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address

RM			=	rm -rf

INC_DIR		=	inc/

SRC_DIR		=	src/

OBJ_DIR		=	temp/

CLASS_DIR	=	classes/

LINKS		=	-lGL -lGLU -lglut

SRC			=	$(addprefix $(SRC_DIR),					main.cpp \
							$(addprefix $(CLASS_DIR),	Engine.cpp))

OBJ_DIRS	=	$(OBJ_DIR) $(addprefix $(OBJ_DIR), 		$(CLASS_DIR))

OBJ			=	$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

GREEN		=	\033[0;32m

RED			=	\033[0;31m

RESET		=	\033[0m

SUS			=	\U00000D9E

HAMMER		=	\U0001F528

BROOM		=	\U0001F9F9

$(NAME):		$(OBJ) | $(SRC)
				printf '$(HAMMER)\t$(GREEN)Compiling $(NAME)$(RESET)\n'
				$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) 
				make compiled

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp | $(OBJ_DIRS)
				printf '$(HAMMER)\t'
				printf "$(GREEN)Compiling $(NAME) objects... $(RED)%-33.33s\r" $(notdir $@)
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(LINKS)

$(OBJ_DIRS):
				mkdir -p $@

all:			$(NAME)

clean:
				if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
				if [ -d $(DEBUG_DIR) ]; then $(RM) $(DEBUG_DIR); fi

fclean:			clean
				printf '$(BROOM)\n$(BROOM)\t$(GREEN)Cleaning project$(RESET)\n'
				$(RM) $(NAME)
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
