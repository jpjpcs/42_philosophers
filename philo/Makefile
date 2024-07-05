# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 11:16:15 by joaosilva         #+#    #+#              #
#    Updated: 2024/07/02 12:07:47 by joaosilva        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######################  Variables ######################
NAME = philo
# NAME_BONUS = so_long_bonus
#Other Variables
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=thread #-fsanitize=address
INCLUDE = -I philo/include

############  Source files - Sources to objects ###########
SRC_FILES = main.c init_philosophers_program.c threads.c routine.c eats_utils.c error_exit_free.c utils.c 
SRC_DIR = src/
SRC = ${addprefix ${SRC_DIR}, ${SRC_FILES}}

########### Object files ###########
OBJ_DIR = objects/
OBJS = ${addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o}}

############ Header files same folder ###########
HEADER_FILES = philo.h
#HEADER_BONUS_FILES = so_long_bonus.h
HEADER_DIR = include/
HEADER = ${addprefix ${HEADER_DIR}, ${HEADER_FILES}}

#######################   Rules ######################
### cria o so_long. congrega todos os ficheiros objetos, o header, o libft e a minilibx.
all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created$(DEF_COLOR)"
	
### criar a diretoria obj e cria os objetos a partir dos ficheiros .c
${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
	@echo "$(GRAY) Object $(basename $(notdir $@)) files created with success$(DEF_COLOR)"

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Object files removed$(DEF_COLOR)"

### remove o so_long
fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed$(DEF_COLOR)"
### primeiro faz o fclean (ou seja, o clean, eliminando os objetos, e dps elimina o libft.a), e a seguir torna a compilar tudo com o all (os objetos e o libft.a)
re: fclean all

### phony faz com que o nome destes comandos não sejam confundidos com ficheiros. ou seja, se houver um ficheiro com esse nome para ser compilado ou atualizado, o compilador ignora.
.PHONY: all clean fclean re bonus

### o silent faz com que as ações ocorram, mas que não apareçam no terminal. Daí o nome silent, pq apesar de ocorreram as ações, elas são silenciosas...não aparecem no terminal.
#.SILENT:

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

git :
	@ clear && sleep 1 && echo "$(RED)\n\n\n\nStart cleanning...\n\n" && sleep 1
	@ make fclean
	@ echo "$(CYAN)\n\n\n\nEverything clean\n\n\n$(GREEN)Git status:\n\n$(DEF_COLOR)"
	@ git status && sleep 1 && echo "$(RED)Press Enter to confirm" && read enter
	@ echo "$(DEF_COLOR)\nGit add everything\n\n"
	@ git add . && git status
	@ echo "$(YELLOW)" && read -p "Enter commit message: " message && read -p "Enter commit comment: " comment && git commit -m "$message" -m "$comment"
	@ echo "$(GRAY)" && git push
	@ echo "$(GREEN)\n\nGit push done with sucess\n\n$(DEF_COLOR)"

#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+SO_LONG MAKEFILE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#*******************+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#######################  Variables ######################
#NAME = so_long
# NAME_BONUS = so_long_bonus

############  Mandatory files - Sources to objects ###########
#SRC_FILES = main.c check_map.c exit.c init_game.c key_press.c so_long.c
#SRC_DIR = src
#SRC = ${addprefix ${SRC_DIR}/, ${SRC_FILES}}
# SRC = $(addsuffix .c, $(SRC_FILES))
############  Bonus files ###########
#SRC_BONUS_FILES = main_bonus.c check_map_bonus.c exit_bonus.c \
					init_enemy_bonus.c init_game_bonus.c key_press_bonus.c \
					render_move_bonus.c game_loop_bonus.c eric_trump_bonus.c
#SRC_BONUS_DIR = src_bonus
#SRC_BONUS = ${addprefix ${SRC_BONUS_DIR}/, ${SRC_BONUS_FILES}}
#SRC_BONUS = $(addsuffix .c, $(SRC_BONUS_FILES))



########### Object files ###########
#OBJS = ${addprefix obj/, ${SRC_FILES:.c=.o}}
#OBJ = $(addsuffix .o, $(SRC_FILES))
#OBJS_BONUS = ${addprefix obj_bonus/, ${SRC_BONUS_FILES:.c=.o}}
#OBJ_BONUS = $(addsuffix .o, $(SRC_BONUS_FILES))

############ Header files same folder ###########
#HEADER_FILES = so_long.h
#HEADER_BONUS_FILES = so_long_bonus.h
#HEADER_DIR = include
#HEADER = ${addprefix ${HEADER_DIR}/, ${HEADER_FILES}}
#HEADER_BONUS = ${addprefix ${HEADER_DIR}/, ${HEADER_BONUS_FILES}}


###Libft
#LIBFT = -L Libft_obj -lft

###GNL
#GET_NEXT_LINE = -L get_next_line_obj -lgnl

# Other Variables
#INCLUDE = -I .
#CC = cc
#RM = rm -f
#CFLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=thread #-fsanitize=address

# Variáveis/Caminho para MiniLibX no Linux
#MINILIBX_LINUX = -L minilibx-linux -lmlx -lXext -lX11

# Variáveis/CAminho para MiniLibX no macOS
#MINILIBX_MACOS = -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

# Verifica o sistema operacional
#UNAME_S := $(shell uname -s)

# este dá erro:  Escolhe as variáveis apropriadas com base no sistema operacional
#ifeq ($(UNAME_S),Linux)
#    MINILIBX = $(MINILIBX_LINUX)
#else ifeq ($(UNAME_S),Darwin)
#    MINILIBX = $(MINILIBX_MACOS)
#else
#    $(error Sistema operacional não suportado: $(UNAME_S))
#endif

# Escolhe as variáveis apropriadas com base no sistema operacional
#ifeq ($(UNAME_S),Linux)
#    MINILIBX = -L minilibx-linux -lmlx -lXext -lX11
#else ifeq ($(UNAME_S),Darwin)
#    MINILIBX = -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
#else
#    $(error Sistema operacional não suportado: $(UNAME_S))
#endif


#######################   Rules ######################
### cria o so_long. congrega todos os ficheiros objetos, o header, o libft e a minilibx.
#all: ${NAME}
#${NAME}: ${OBJS} ${HEADER}
#	@make -s -C Libft
#	@make -s -C get_next_line
#ifeq ($(UNAME_S),Linux)
#	@make -s -C minilibx-linux
#else 
#	@make -s -C minilibx_opengl_20191021
#minilibx_macos:
#	@make -C minilibx_opengl_20191021
#	@echo "$(GREEN)\nCompilando MiniLibX para macOS...$(DEF_COLOR)"
#endif
#	@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS} 
#	@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS} ${LIBFT} ${GET_NEXT_LINE} ${MINILIBX}
#	@echo "$(GREEN)\n${NAME} created$(DEF_COLOR)"


###criar a diretoria obj e cria os objetos a partir dos ficheiros .c
#obj/%.o: ${SRC_DIR}/%.c ${HEADER}
#	@mkdir -p $(dir $@)
#	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
#	@echo "$(GRAY) Object $(basename $(notdir $@)) files created with success$(DEF_COLOR)"

#bonus: ${NAME_BONUS}

#${NAME_BONUS}: ${OBJS_BONUS} ${HEADER_BONUS}
#	@make -s -C Libft
#	@make -s -C minilibx-linux
#	@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME_BONUS} ${OBJS_BONUS} ${LIBFT} ${MINILIBX}
#	@echo "\n${NAME_BONUS} created"

#obj_bonus/%.o: ${SRC_BONUS_DIR}/%.c
#	@mkdir -p obj_bonus
#	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
#	@echo "\nObject files created"



### remove os objetos e os objetos do bonus, assim como a pasta que os recebeu.
#clean:
#	@make fclean -s -C Libft
#	@make clean -s -C minilibx-linux
#	@${RM} ${OBJS}
#removed ${OBJS_BONUS} at the above rm
#	@${RM} -r obj
#removed obj_bonus at the above rm
#	@echo "$(RED)\nObject files removed$(DEF_COLOR)"

#clean:
#	@make fclean -s -C Libft
#	@make fclean -s -C get_next_line
#ifeq ($(UNAME_S),Linux)
#	@make clean -s -C minilibx-linux
#	@${RM} -r minilibx-linux
#	@${RM} -r minilibx-linux.tgz
#else ifeq ($(UNAME_S),Darwin)
#	@${RM} -r minilibx_opengl_20191021
#	@${RM} -r minilibx_opengl.tgz
# @make clean -C minilibx_opengl_20191021
# @make clean -s -C minilibx_opengl_20191021
#endif
#	@${RM} ${OBJS}
#	@${RM} -r obj
#	@echo "$(RED)\nObject files removed$(DEF_COLOR)"


###remove o so_long
#fclean: clean
#	@${RM} ${NAME}
#removed ${NAME_BONUS} at the above rm
#	@echo "$(RED)\n${NAME} removed$(DEF_COLOR)"



###shell script para iniciar o jogo
#run:
#	@MAP_COUNT=$$(find maps -maxdepth 1 -type f | wc -l); \
	read -p "Pick a map, options 0 to $$(($$MAP_COUNT-2)): " MAP_FILE; \
	if [ -x "so_long_bonus" ]; then \
		./so_long_bonus maps/$$MAP_FILE.ber; \
	elif [ ! -x "so_long" ]; then \
		echo "$(YELLOW)Neither the game so_long nor so_long_bonus was found. Compile the desired game and run again.$(DEF_COLOR)"; \
	else \
		./so_long maps/$$MAP_FILE.ber; \
	fi



###shell script para iniciar o jogo
#runall:
#	@MAP_COUNT=$$(find maps -maxdepth 1 -type f | wc -l); \
	read -p "Select starting map (0 to $$((MAP_COUNT-2))): " i; \
	while [ $$i -lt $$MAP_COUNT ]; do \
		echo "$(CYAN)Running map $$i...$(DEF_COLOR)"; \
		if [ -x "so_long_bonus" ]; then \
			output=$$(./so_long_bonus maps/$$i.ber); \
		else \
			output=$$(./so_long maps/$$i.ber); \
		fi; \
		echo "$$output" | grep -q "Game ended! You have eaten all cheese 🧀🧀🧀 🐁"; \
		if [ $$? -eq 0 ]; then \
			echo "$(CYAN)\nMap $$i completed.$(DEF_COLOR)"; \
			i=$$(($$i + 1)); \
		fi; \
		echo "$(CYAN)$$output"; \
		if [ $$i -ge $$MAP_COUNT ]; then \
			echo "$(CYAN)\nAll maps completed.$(DEF_COLOR)"; \
			break; \
		fi; \
		echo "$(CYAN)\nStarting map $$i.$(DEF_COLOR)"; \
		read -p "Continue? (y/n): " choice; \
		if [ $$choice != "y" ]; then \
			break; \
		fi; \
		sleep 1; \
	done



###o fcleansoft existe para uma versão soft da compilação, sem incluir a biblioteca, senão além de demorar muito, gastamos recursos desnecessariamente.
#fcleansoft:
#	@${RM} ${OBJS}
#removed ${OBJS_BONUS} at the above rm
#	@${RM} -r obj
#removed obj_bonus at the above rm
#	@echo "$(RED)\nObject files removed$(DEF_COLOR)"
#	@${RM} ${NAME}
#removed ${NAME_BONUS} at the above rm
#	@echo "$(RED)\n${NAME} removed$(DEF_COLOR)"



###faz download automático da biblioteca, diretamente da página do intra.
#downloadminilibx:
#	@wget https://projects.intra.42.fr/so_long/jode-jes#:~:text=minilibx%2Dlinux.tgz-,minilibx_opengl.tgz,-minilibx_mms_20200219_beta.tgz
#	@tar -xzf minilibx-linux.tgz


# Verifica o sistema operacional
#UNAME_S := $(shell uname -s)

# Define o comando de download e descompactação com base no sistema operacional
#ifeq ($(UNAME_S),Linux)
#    DOWNLOAD_CMD := wget
#    TAR_CMD := tar -xzf
#    MINILIBX_URL := https://cdn.intra.42.fr/document/document/21300/minilibx-linux.tgz
#else
#    DOWNLOAD_CMD := curl -LO
#    TAR_CMD := tar -xzf
#    MINILIBX_URL := https://cdn.intra.42.fr/document/document/21301/minilibx_opengl.tgz

#endif

#downloadminilibx:
#	@$(DOWNLOAD_CMD) $(MINILIBX_URL)
#	@$(TAR_CMD) $(shell basename $(MINILIBX_URL))
#	@$(TAR_CMD) $(notdir $(MINILIBX_URL))
#ifeq ($(UNAME_S),Linux)
#	@echo "$(GREEN)\n MINILIBX LINUX downloaded and folder created$(DEF_COLOR)"
#else
#	@echo "$(GREEN)\n MINILIBX MacOS downloaded and folder created$(DEF_COLOR)"
#endif

#cleanlibrary:
#ifeq ($(IS_LINUX),1)
#	@${RM} -rf minilibx-linux
#	@echo "$(RED)\n MINILIBX LINUX objects cleaned and folder deleted$(DEF_COLOR)"
#else
#	@${RM} $(notdir $(MINILIBX_URL))
#	@${RM} -rf minilibx_opengl_20191021
#	@echo "$(RED)\n MINILIBX MacOS objects cleaned and folder deleted$(DEF_COLOR)"
#endif



### primeiro faz o fclean (ou seja, o clean, eliminando os objetos, e dps elimina o libft.a), e a seguir torna a compilar tudo com o all (os objetos e o libft.a)
#re: fclean all



### o rebsoft existe para uma versão soft da compilação, sem incluir a biblioteca
#rebsoft: fcleansoft bonus


# Colors
#DEF_COLOR = \033[0;39m
#GRAY = \033[0;90m
#RED = \033[0;91m
#GREEN = \033[0;92m
#YELLOW = \033[0;93m
#BLUE = \033[0;94m
#MAGENTA = \033[0;95m
#CYAN = \033[0;96m
#WHITE = \033[0;97m


#git :
#	@ clear && sleep 1 && echo "$(RED)\n\n\n\nStart cleanning...\n\n" && sleep 1
#	@ make fclean
#	@ echo "$(CYAN)\n\n\n\nEverything clean\n\n\n$(GREEN)Git status:\n\n$(DEF_COLOR)"
#	@ git status && sleep 1 && echo "$(RED)Press Enter to confirm" && read enter
#	@ echo "$(DEF_COLOR)\nGit add everything\n\n"
#	@ git add . && git status
#	@ echo "$(YELLOW)" && read -p "Enter commit message: " message && read -p "Enter commit comment: " comment && git commit -m "$message" -m "$comment"
#	@ echo "$(GRAY)" && git push
#	@ echo "$(GREEN)\n\nGit push done with sucess\n\n$(DEF_COLOR)"



### phony faz com que o nome destes comandos não sejam confundidos com ficheiros. ou seja, se houver um ficheiro com esse nome para ser compilado ou atualizado, o compilador ignora.
#.PHONY: all clean fclean re bonus



### o silent faz com que as ações ocorram, mas que não apareçam no terminal. Daí o nome silent, pq apesar de ocorreram as ações, elas são silenciosas...não aparecem no terminal.
#.SILENT: