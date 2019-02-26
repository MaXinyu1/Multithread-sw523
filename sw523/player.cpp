//
//  player.cpp
//  sw523
//
//  Created by maxinyu on 2019/2/8.
//  Copyright © 2019年 maxinyu. All rights reserved.
//

#include <iostream>
#include "player.hpp"
using namespace std;

player::player(string NAME, string SEX, int LEVEL, int BEANS):name(NAME), sex(SEX), level(LEVEL), beans(BEANS){};
player::~player(){};
