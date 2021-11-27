#pragma once
#include <stdlib.h>
#include "image.h"
#include "Settings.h"
#include "role.h"

typedef struct Bullet {
  int x, y;
  int player;
  int direction;
  struct Bullet* next;
} bullet;

extern bullet* bullethead;
extern bullet* bullettail;

void initbullet();
void addbullet(int rolenum);
int getbulletx(bullet* p);
int getbullety(bullet* p);
int getbulletendx(bullet* p);
void deletebullet();
void updatabullet();
void clearbullet();