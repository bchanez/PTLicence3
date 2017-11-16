EXENAME := app

DIRECSRC := ./src
DIRECBIN := ./bin
DIRECOBJ := ./obj

CC := g++ -std=c++14 #-O3
CFLAGS := -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlogical-op -Winline

LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES :=

SRC := $(shell find $(DIRECSRC) -name '*.cpp')
OBJ := $(SRC:.cpp=.o)


all: $(EXENAME) install

$(EXENAME): $(OBJ)
	@echo "** Building the game"
	$(CC) -o $(DIRECSRC)/$@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install:
	@echo "** Installing..."
	sh ./rsc/Tools/creerRepertoires.sh
	cp $(DIRECSRC)/$(EXENAME) $(DIRECBIN)
	cp $(OBJ) $(DIRECOBJ)
	chmod u+x $(DIRECBIN)/$(EXENAME)

clean:
	@echo "** Removing object files and executable..."
	rm -f $(OBJ)
	rm -f $(DIRECSRC)/$(EXENAME)

execute:
	@echo "** start the game.."
	$(DIRECBIN)/$(EXENAME)
