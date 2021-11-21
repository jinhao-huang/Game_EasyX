#include "role.h"

struct Role role[2];

bool isinside(int x, int y, int rolenum) {
  if (role[rolenum].direction == rightdire) {
    if (x > role[rolenum].x + 78 && x < role[rolenum].x + 124
      && y > role[rolenum].y + 54 && y < role[rolenum].y + 132) {
      return true;
    }
    else return false;
  }
  else {
    if (x > role[rolenum].x + 76 && x < role[rolenum].x + 122
      && y > role[rolenum].y + 54 && y < role[rolenum].y + 132) {
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
  return;
}