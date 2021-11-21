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
void updatabullet();
void deletebullet();