# Chain Reaction Framework

Readme url: [Readme](https://github.com/Echodarius/Chain_reaction_game/edit/master/README.md)
TA's readme url: [TA's Readme](https://gitlab.com/tzuyangw/chain-reaction-framework/blob/master/README.md)
The spec document: [Demand](https://gitlab.com/tzuyangw/chain-reaction-framework/blob/master/Demand.pdf)

# A project homework of Data Structure written by C++ language.
The framework is applyed by TA, I need to implement an AI bot to defeat TA's bot.
My work are Minimax.cpp, algorithm_A.cpp, QuickSort.cpp, the other codes are TA's.

## Compile Command:
* $g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_A.cpp algorithm_TA.cpp

## Execution: 
* Execute the output file(Mac: a.out, Windows: a.exe)

## Description 

### Main program

*  The main data flow is in the chain_reaction.cpp. 
*  The following three lines of code are used to declare the variable board, red player and blue player.<br></br>

![Variable Declaration](/images/002.png)

*  Firstly, the program will call your function which "should" return a board index (i, j).
*  Then the program will call place_orb function to put your orb on the index that obtained from your algorithm.
*  If a players' placement is illegal, the program will terminate immediately and annouce the winner.
*  If a players' last placement dominate the hole board, the program will terminate immediately and annouce the winner.

![Player action](/images/001.png)

### Algorithm_A

* Implement Minimax strategy for the bot.

### Minimax
* The heuristic strategy is from [Brilliant](https://brilliant.org/wiki/chain-reaction-game/)

### QuickSort
* Partition : 3-way partition
* Pivot: Median of three
* descending order
