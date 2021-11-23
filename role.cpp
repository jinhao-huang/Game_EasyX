#include "role.h"

struct Role role[2];

int rrole_rm = 123; // right role's right margin and so on
int rrole_lm = 75;
int lrole_rm = 126;
int lrole_lm = 78;
int role_tm = 53; //role's top margin
int role_bm = 132; //role's bottom margin
IMAGE hp1;
IMAGE hp2;

bool isinside(int x, int y, int rolenum) {
  if (role[rolenum].direction == rightdire) {
    if (x > role[rolenum].x + rrole_lm && x < role[rolenum].x + rrole_rm
      && y > role[rolenum].y + role_tm && y < role[rolenum].y + role_bm) {
      return true;
    }
    else return false;
  }
  else {
    if (x > role[rolenum].x + lrole_lm && x < role[rolenum].x + lrole_rm
      && y > role[rolenum].y + role_tm && y < role[rolenum].y + role_bm) {
      return true;
    }
    else return false;
  }
}

void reborn(struct Role& role) {
  role.x = bornx[role.num];
  role.y = borny[role.num];
  role.hp = initialhp;
  role.vy = 0;
  role.vx = 0;
  hp1 = gameimage.hp;
  hp2 = gameimage.hp;
  return;
}