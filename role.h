#pragma once
#include "Settings.h"
#include "image.h";

enum dire {
	leftdire = -1,
	rightdire = 1
};

struct Role {
	double x, y;
	int hp = initialhp; //health point
	int direction = rightdire;
	double vy = 0;
	double vx = 0;
	int num;
};

bool isinside(int x, int y, int rolenum);
void reborn(struct Role& role);
extern struct Role role[2];

extern int rrole_rm;
extern int rrole_lm;
extern int lrole_rm;
extern int lrole_lm;
extern int role_tm;
extern int role_bm;
extern IMAGE hp1;
extern IMAGE hp2;