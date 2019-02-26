# Multithread-sw523

## Description
This project implements a card game named 7king523.  

It is develops in 2 steps:
- [x] Build a single thread 7king523 (all players play in one terminal)
- [ ] Build miltithread 7king523 (players can play in their own terminals, so that they can not see each others cards)

## Rules
Here is the rules of the game.
1. 7 > 0 (king) > 5 > 2 > 3 > 1 > 13(k) > 12(Q) > 11(J) > 10 > 9 > 8 > 6 > 4
2. Each player only have 5 cards on hand. After each round end, they can get cards from the card board.
3. If you are the first player, you can choose any cards you have. Otherwise, you can only choose cards equal or lager than your previous player, both the value and the number of cards.
4. 0 (king),13(k),10 are credits
5. Each round, the player who ends the play wins the credits.
6. After finishing all cards, the player who has the most credit wins.


## Instructions To Run
**1. Use your compiler build and compile the server**

**2. Input player numbers and Wait others to login the game**  

**3. Copy as many clients(players) as you want and compile your code. The clients will automatically link to server**  

**4. After all the players are in, players input their infomations (name, gender, level, beans)**  

**5. Game starts and players input the index of the cards, 5 is to skip**  

**6. After one player finishing his/her all card, game end. Show the credit board**

## Project Structure
```bash
├── README.md
├───sw523
│   ├───*server.cpp
│   ├───*cards.cpp
│   ├───*cards.hpp
│   ├───*player.cpp
│   └───*player.hpp  
└───client
    └───*client.cpp
```


## Developer
- Xinyu Ma
