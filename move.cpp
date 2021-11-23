#include "move.h"
#include "test.h"
bool jump[2] = { false };
bool land[2] = { false };
int floor = -1;

bool island(struct Role& role) {
  if (role.x >= 463 && role.x <= 589
    && role.y >= 14 && role.y < 19) {
    role.y = 14;
    return true;
  }
  if (role.x >= 302 && role.x <= 740
    && role.y >= 91 && role.y < 96) {
    role.y = 91;
    return true;
  }
  if (role.x >= 129 && role.x <= 270
    && role.y >= 152 && role.y < 157) {
    role.y = 152;
    return true;
  }
  if (role.x >= 761 && role.x <= 884
    && role.y >= 152 && role.y < 157) {
    role.y = 152;
    return true;
  }
  if (role.x >= 69 && role.x <= 386
    && role.y >= 233 && role.y < 238) {
    role.y = 233;
    return true;
  }
  if (role.x >= 615 && role.x <= 925
    && role.y >= 233 && role.y < 238) {
    role.y = 233;
    return true;
  }
  if (role.x >= 394 && role.x <= 593
    && role.y >= 305 && role.y < 310) {
    role.y = 305;
    return true;
  }
  if (role.x >= 74 && role.x <= 455
    && role.y >= 368 && role.y < 373) {
    role.y = 368;
    return true;
  }
  if (role.x >= 551 && role.x <= 950
    && role.y >= 368 && role.y < 373) {
    role.y = 368;
    return true;
  }
  return false;
}

void move1(struct Role &role, clock_t time) {
  
  if (presskey[UP_KEY] && land[0] == true) {
    land[0] = false;
    role.vy = -400;
  }
  else
  {
    if (presskey[UP_KEY] && land[0] == false && jump[0] == false) {
      jump[0] = true;
      role.vy = -400;
    }
  }

  if (presskey[DOWN_KEY]) {
    if (land[0] == true) {
      land[0] = false;
      role.vy = 0;
      role.y += 5;
    }
  }

  if (presskey[LEFT_KEY]) {
    role.x -= movespeed * time;
    role.direction = leftdire;
  }

  if (presskey[RIGHT_KEY]) {
    role.x += movespeed * time;
    role.direction = rightdire;
  }
  if (land[0] == true) {
    land[0] = island(role);
  }
  if (land[0] == false) {
    role.y += role.vy * (time / 1000.0);
    role.vy += g * (time / 1000.0);
    if (island(role) && role.vy >= 0) {
      land[0] = true;
      jump[0] = false;
      role.vy = 0;
      floor = island(role);
    }
  }
  if (role.vx > 0) {
    role.x += role.vx * (time / 1000.0);
    role.vx -= gx * (time / 1000.0);
    if (role.vx < 0) {
      role.vx = 0;
    }
  }
  else if (role.vx < 0) {
    role.x += role.vx * (time / 1000.0);
    role.vx += gx * (time / 1000.0);
    if (role.vx > 0) {
      role.vx = 0;
    }
  }
  return;
}

void move2(struct Role& role, clock_t time) {

#if __FIND__
  if (presskey[UP2_KEY]) {
    role.y -= movespeed;
  }
  if (presskey[DOWN2_KEY]) {
    role.y += movespeed;
  }
#endif

#if !__FIND__
  if (presskey[UP2_KEY] && land[1] == true) {
    land[1] = false;
    role.vy = -400;
  } else
    if (presskey[UP2_KEY] && land[1] == false && jump[1] == false) {
      jump[1] = true;
      role.vy = -400;
    }
#endif
  if (presskey[DOWN2_KEY]) {
    if (land[1] == true) {
      land[1] = false;
      role.vy = 0;
      role.y += 5;
    }
  }
  if (presskey[LEFT2_KEY]) {
    role.x -= movespeed * time;
    role.direction = leftdire;
  }

  if (presskey[RIGHT2_KEY]) {
    role.x += movespeed * time;
    role.direction = rightdire;
  }
#if !__FIND__
  if (land[1] == true) {
    land[1] = island(role);
  }
  if (land[1] == false) {
    role.y += role.vy * (time / 1000.0);
    role.vy += g * (time / 1000.0);
    if (island(role) && role.vy >= 0) {
      land[1] = true;
      jump[1] = false;
      role.vy = 0;
      floor = island(role);
    }
  }
#endif
  if (role.vx > 0) {
    role.x += role.vx * (time / 1000.0);
    role.vx -= gx * (time / 1000.0);
    if (role.vx < 0) {
      role.vx = 0;
    }
  }
  else if (role.vx < 0) {
    role.x += role.vx * (time / 1000.0);
    role.vx += gx * (time / 1000.0);
    if (role.vx > 0) {
      role.vx = 0;
    }
  }
  return;
}