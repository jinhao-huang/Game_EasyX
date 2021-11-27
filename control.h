#include <graphics.h>
#include "image.h"
#include "bullet.h"
#include "key.h"
#pragma once
#ifndef __con__
#define __con__

enum stateval{
  menu,
  game,
  over,
  back,
  state_setting
};


void startgame();
void initgame();
void initsettings();
void writesettings();
int centerx(IMAGE& back, IMAGE& front);

extern LOGFONT myfont;
extern int state;
extern bool playbgmusic;
extern FILE* fp;
#endif