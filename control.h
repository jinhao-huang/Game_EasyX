#pragma once

enum stateval {
  menu,
  game,
  over
};

void startgame();
void initgame();
int centerx(IMAGE& back, IMAGE& front);

extern int state;
extern bool playbgmusic;