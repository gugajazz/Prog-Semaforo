# Prog Semaforo
## _A C board game built for my programing course._

If you are interested in a more detailed description please refere to my report, present in the following file ```Relatorio Prog.pdf```

## Running it and rules

Open the folder and run ``gcc -o main *.c`` -> ``./main.exe``

Now to play attempt to fill a line/column/diagonal with the same color.
The squares change color according to the order ````Empty->Green->Yellow->Red````.
You can't place a color where a stone lays.
You can only place one stone and increase the board size two times each game.


## Features
- See the history of board states (implemented as a linked list)
- Dynamically allocated board allowing for resizing (2d array)
- 1 or 2 player modes
- Exporting history of board states to a txt file
- Random starting board size


## Images


![alt text](https://github.com/gugajazz/Prog-Semaforo/blob/main/imgs/jogar.png?raw=true)
<br><br>

![alt text](https://github.com/gugajazz/Prog-Semaforo/blob/main/imgs/historico.png?raw=true)

