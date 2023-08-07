SOURCE = 2107067
FLAGS = -std=c++20 -Wall -Werror -g0 -O2

all:
	rm -f $(SOURCE) *.o *.DSYM
	g++ $(FLAGS) $(SOURCE).cpp -o $(SOURCE) && ./$(SOURCE)

clean:
	rm -f $(SOURCE) *.o *.DSYM