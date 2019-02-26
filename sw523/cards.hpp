//
//  cards.hpp
//  sw523
//
//  Created by maxinyu on 2019/2/8.
//  Copyright © 2019年 maxinyu. All rights reserved.
//

#ifndef __HEAD_CARDS_ // to prevent iterate include
#define __HEAD_CARDS_

#include <iostream>
#include <vector>
//#include "player.hpp"
using namespace std;

class player;

enum Suit {heart, spade, diamond, club, joker1, joker2};

struct card {
    int num;
    enum Suit suit;
};

class cards {
private:
    enum Suit su[4] = { heart, spade, diamond, club};
public:
    
    vector<card> c; //cards
    
    cards(){};
    ~cards();
    void createCards(int ammount);
    
    void shuffleCards();
    
    void dealCards(vector<player*> &players);
    
    void game(vector<player*> players);
    
    void play(player* p, int &now, int &count, vector<int>& turn, int num, int &credit_one_round);
    
    bool check(player* p, int &now, int &count, vector<int> &choose, int& credit_one_round);
    
    void refill(player* p);
};

#endif
