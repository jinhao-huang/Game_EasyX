#include "bullet.h"
#include <stdio.h>


bullet* bullethead;
bullet* bullettail;



void initbullet() {
  bullethead = (bullet*)malloc(sizeof(bullet));
  bullettail = bullethead;
  if (bullethead == NULL)
    exit(ERROR);
  else {
    bullethead->next = NULL;
  }
  
}

void addbullet(int rolenum) {
  bullet* newbullet = (bullet*)malloc(sizeof(bullet));
  if (newbullet == NULL) {
    exit(ERROR);
  }
  else {
    newbullet->player = rolenum;
    newbullet->next = NULL;
    newbullet->direction = role[rolenum].direction;
    if (newbullet->direction == rightdire) {
      newbullet->x = role[rolenum].x + 115;
      newbullet->y = role[rolenum].y + 95;
    }
    else {
      newbullet->x = role[rolenum].x + 10;
      newbullet->y = role[rolenum].y + 95;
    }

    bullettail->next = newbullet;
    bullettail = newbullet;
  }
}

inline int getbulletx(bullet *p) {
  if (p->direction == rightdire) {
    return (p->x) + 85;
  }
  else {
    return p->x;
  }
}

inline int getbullety(bullet* p) {
  return (p->y) + 2;
}

void deletebullet() {
  bullet* deletep;
  bullet* p = bullethead;
  while (p->next != NULL) {
    bool isdelete = false;

    //is shooted
    int bulletx = getbulletx(p->next);
    int bullety = getbullety(p->next);
    int shotrole = p->next->player == 0 ? 1 : 0;
    isdelete = isinside(bulletx, bullety, shotrole);
    if (isdelete) {
      role[shotrole].hp--;
      role[shotrole].vx = (p->next->direction) * (300);
    }

    //over edge
    if (p->next->x > 2000 || p->next->x < -1000) {
      isdelete = true;
    }
    if (isdelete) {
      deletep = p->next;
      p->next = deletep->next;
      if (deletep == bullettail) {
        bullettail = p;
      }
      free(deletep);
    }
    if (!isdelete) {
      p = p->next;
    }
  }
}

void updatabullet() {
  deletebullet();

  //draw bullet
  for (bullet* p = bullethead->next; p != NULL; p = p->next) {
    if (p->direction == rightdire) {
      putimage(p->x, p->y, &gameimage.bullet[0], SRCAND);
      putimage(p->x, p->y, &gameimage.bullet[1], SRCINVERT);
    }
    else {
      putimage(p->x, p->y, &gameimage.bullet_left[0], SRCAND);
      putimage(p->x, p->y, &gameimage.bullet_left[1], SRCINVERT);
    }
    p->x = p->x + (bulletspeed * (p->direction));
  }
  return;
}