#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "show.h"
#include "control.h"
#pragma once

extern int width;
extern int height;
extern double movespeed;
extern double backstrength;
extern int bulletspeed;
extern int gap_time;
extern double g;
extern double gx;
extern char player1[128];
extern char player2[128];
extern int rolelives;

extern int initialhp;

extern double bornx[2];
extern double borny[2];

void showsettings();
void changesetting(int& settings);
void changesetting(char* par);