#pragma once

enum stateval {
  menu,
  game,
  over,
  back
};


void startgame();
void initgame();
void initsettings(FILE* fp);
void writesettings(FILE* fp);
int centerx(IMAGE& back, IMAGE& front);

extern int state;
extern bool playbgmusic;