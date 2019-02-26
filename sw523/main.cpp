//
//  main.cpp
//  sw523
//
//  Created by maxinyu on 2019/2/8.
//  Copyright © 2019年 maxinyu. All rights reserved.
//

/*
 1.UI
 2.multithreading server (different user different server)
 */

/***************SW523 Game Rules***************/
/*
 1.press 5 to skip
 2.press 9 to finish input
 3. 7 > 0 > 5 > 2 > 3 > 1 > 13 > 12 > 11 > 10 > 9 > 8 > 6 > 4
 4. 10 and 13 are credits
 5. the person who got the most credit wins
 */
 
#include <iostream>
#include <vector>
#include "cards.hpp"
#include "player.hpp"
using namespace std;

int main() {
    //create player
    int player_num;
    cout<<"How many players: ";
    cin>>player_num;
    
    vector<player*> p;
    string name, sex;
    int level, beans;
    
    for(int i = 0; i < player_num; i++) {
        cin>>name>>sex>>level>>beans;
        player *newp = new player(name,sex,level,beans);
        p.emplace_back(newp);
    }
    
    
    //create cards
    cards *c = new cards;
    int card_num;
    cout<<"How many card: ";
    cin>>card_num;
    c->createCards(card_num);
    
    //shuffle cards
    c->shuffleCards();
    
    //deal cards
    c->dealCards(p);
    
    //play game
    c->game(p);
}
