//
//  cards.cpp
//  sw523
//
//  Created by maxinyu on 2019/2/8.
//  Copyright © 2019年 maxinyu. All rights reserved.
//

#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>
#include "cards.hpp"
#include "player.hpp"
using namespace std;

void cards::createCards(int ammount) {
    vector<card> v(54);
    v[0] = {0, joker1};
    v[1] = {0, joker2};
    int p = 2;
    for(int i = 1; i <= 13; i++) {
        for(int j = 0; j < 4; j++) {
            v[p] = {i, su[j]};
            p++;
        }
    }
    for(int i = 0; i < ammount; i++) {
        c.insert(c.end(), v.begin(), v.end());
    }
}

void cards::shuffleCards() {
    srand((int)time(NULL)); //to make sure each time shuffle the cards, we can get a different conbination
    int size = (int)c.size();
    vector<card> newc(size);
    for(int i = 0; i < size; i++) {
        int index = rand()%c.size();
        newc[i] = c[index];
        c.erase(c.begin()+index);
    }
    c = newc;
}

void cards::dealCards(vector<player*> &players) {
    
    int player_num = (int)players.size();
    int i = 0;
    int card_num = (int)c.size();
    while(i < 5*player_num) {
        int j = 0;
        while(i < card_num && j < player_num) {
            players[j]->cards.emplace_back(c[i]);
            i++;
            j++;
        }
    }
    c.erase(c.begin(), c.begin()+5*player_num);
}

void cards::game(vector<player*> players){
    int i = 0;
    int now = -1;
    int count = 0;
    int player_num = (int)players.size();
    vector<int> credit(player_num,0);
    while(c.size() != 0) {
        //init
        now = -1;
        count = 0;
        
        //play in turn
        vector<int> turn(player_num,1);
        int credit_one_round = 0;
        while(!(accumulate(turn.begin(),turn.end(),0) == 1 && turn[i] == 1)) {
            cout<<"player "<<i<<" turn: ";
            play(players[i], now, count, turn, i, credit_one_round);
            cout<<endl;
            i++;
            if(i == player_num) i = 0;
        }
        
        //collect credit
        credit[i] += credit_one_round;
        
        //refill card
        int position = i;//i-1 >= 0 ? i-1 : player_num-1;
        while(1) {
            refill(players[i]);
            i++;
            if(i == player_num) i = 0;
            if(i == position) break;
        }
        
    }
    
    //final round
    int flag = 0;
    while(1) { //finish all cards
        //init
        now = -1;
        count = 0;
        
        //play in turn
        vector<int> turn(player_num,1);
        int credit_one_round = 0;
        while(!(accumulate(turn.begin(),turn.end(),0) == 1 && turn[i] == 1)) {
            cout<<"player "<<i<<" turn: ";
            play(players[i], now, count, turn, i, credit_one_round);
            cout<<endl;
            
            if(players[i]->cards.size() == 0) {
                flag = 1;
                break;
            }
            
            i++;
            if(i == player_num) i = 0;
        }
        
        //collect credit
        credit[i] += credit_one_round;
        
        if(flag == 1) break;
    }
    cout<<"Game End !!!"<<endl;
    
    //final credit
    cout<<"Final Credit board: "<<endl;
    i = 1;
    for(auto cc : credit) {
        cout<<"Player "<<i<<": "<<cc<<endl;
        i++;
    }
    cout<<endl;
}

void cards::play(player* p, int &now, int &count, vector<int>& turn, int num, int &credit_one_round) {
    //show cards
    for(auto i : p->cards) {
        cout<<i.num<<" ";
    }
    cout<<endl;
    
    //choose and check
    while(1) {
        cout<<"choose: ";
        vector<int> choose; // record position
        
        //input
        int temp;
        while(cin>>temp) {
            if(temp == 5) {//skip
                turn[num] = 0;
                return;
            }
            if(temp == 9) break; // finish input
            choose.emplace_back(temp);
        }
        
        //validation
        if(check(p, now, count, choose, credit_one_round)) {
            return;
        }
        cout<<"Invalid input !"<<endl;
    }
}

//choose 0 - 4 to choose card
//9 stop choosing
//choose 5 to skip

bool cards::check(player* p, int &now, int &count, vector<int> &choose, int& credit_one_round) {
    if(choose.size() < count) return 0;
    
    int card = p->cards[choose[0]].num;
    for(auto i : choose) {
        if(p->cards[i].num != card) return 0;
    }
    
    int flag = 0;
    if(now == -1) flag = 1; //start
    else if(card == 7) flag = 1; //7
    else if(card == 0 && now != 7) flag = 1; //king
    else if(card == 5 && now != 7 && now != 0) flag = 1; //5
    else if(card == 2 && now != 7 && now != 0 && now != 5) flag = 1; //2
    else if(card == 3 && now != 7 && now != 0 && now != 5 && now != 2) flag = 1; //3
    else if(card == 1 && now != 7 && now != 0 && now != 5 && now != 2 && now != 3) flag = 1; //A
    else if(card == 13 && now <= 13 && now >= 4 && now != 5 && now != 7) {credit_one_round += choose.size();flag = 1;} //K
    else if(card == 12 && now <= 12 && now >= 4 && now != 5 && now != 7) flag = 1; //Q
    else if(card == 11 && now <= 11 && now >= 4 && now != 5 && now != 7) flag = 1; //J
    else if(card == 10 && now <= 10 && now >= 4 && now != 5 && now != 7) {credit_one_round += choose.size();flag = 1;} //10
    else if(card == 9 && now <= 9 && now >= 4 && now != 5 && now != 7) flag = 1; //9
    else if(card == 8 && now <= 8 && now >= 4 && now != 5 && now != 7) flag = 1; //8
    else if(card == 6 && (now == 6 || now == 4)) flag = 1; //6
    else if(card == 4 && now == 4) flag = 1; //4
    
    if(flag == 1) {
        now = card;
        count = (int)choose.size();
        
        //show board
        for(auto ch : choose) cout<<p->cards[ch].num<<" ";
        
        //delete
        unordered_set<int> m(choose.begin(),choose.end());
        for(int i = 0; i < p->cards.size(); i++) {
            if(m.find(i) != m.end()) {
                p->cards[i].num = -1;
            }
        }
        
        int i = 0;
        while(i < p->cards.size()) {
            if(p->cards[i].num == -1) {
                p->cards.erase(p->cards.begin()+i);
                i--;
            }
            i++;
        }

    }
    return flag;
}

void cards::refill(player* p) {
    while(p->cards.size() != 5 && c.size() != 0) {
        p->cards.emplace_back(c[0]);
        c.erase(c.begin());
    }
}
