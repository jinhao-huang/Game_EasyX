#include "bullet.h"


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
      addimage(role[rolenum].x + 123, role[rolenum].y + 79, 20, &gameimage.fire[0], &gameimage.fire[1]);
      newbullet->x = role[rolenum].x + 123;
      newbullet->y = role[rolenum].y + 95;
    }
    else {
      addimage(role[rolenum].x + 32, role[rolenum].y + 79, 20, &gameimage.fire_left[0], &gameimage.fire_left[1]);
      newbullet->x = role[rolenum].x - 8;
      newbullet->y = role[rolenum].y + 95;
    }

    //if bullet close to role
    int shotrole = newbullet->player == 0 ? 1 : 0;
    if (newbullet->direction == rightdire) {
      if (getbulletx(newbullet) >= role[shotrole].x + rrole_rm && getbulletendx(newbullet) <= role[shotrole].x + rrole_rm
        && getbullety(newbullet) >= role[shotrole].y + role_tm && getbullety(newbullet) <= role[shotrole].y + role_bm) {
        role[shotrole].hp--;
        role[shotrole].vx = (newbullet->direction) * (backstrength);
        addimage(role[shotrole].x + 40, role[shotrole].y + 20, 300, &gameimage.hit[0], &gameimage.hit[1]);
        free(newbullet);
        return;
      }
    }
    if (newbullet->direction == leftdire) {
      if (getbulletx(newbullet) <= role[shotrole].x + lrole_lm && getbulletendx(newbullet) >= role[shotrole].x + lrole_lm
        && getbullety(newbullet) >= role[shotrole].y + role_tm && getbullety(newbullet) <= role[shotrole].y + role_bm) {
        role[shotrole].hp--;
        role[shotrole].vx = (newbullet->direction) * (backstrength);
        addimage(role[shotrole].x + 40, role[shotrole].y + 20, 300, &gameimage.hit[0], &gameimage.hit[1]);
        free(newbullet);
        return;
      }
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

inline int getbulletendx(bullet* p) {
  if (p->direction == rightdire) {
    return p->x;
  }
  else {
    return (p->x) + 85;
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
      role[shotrole].vx = (p->next->direction) * (backstrength);
      addimage(role[shotrole].x + 40, role[shotrole].y + 20, 300, &gameimage.hit[0], &gameimage.hit[1]);
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