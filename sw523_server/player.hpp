//
//  player.hpp
//  sw523
//
//  Created by maxinyu on 2019/2/8.
//  Copyright © 2019年 maxinyu. All rights reserved.
//

#ifndef __HEAD_PLAYER_
#define __HEAD_PLAYER_

#include <iostream>
#include "cards.hpp"
#include <vector>
using namespace std;

//template<class T>

struct card;

class player{
public:
    string name;
    string sex; // female or male
    int level;  //0,1,2...
    int beans;
    vector<card> cards;
    player(string NAME, string SEX, int LEVEL, int BEANS);
    ~player();
    void createPlayers(int number);
    int deal();
};

#endif
