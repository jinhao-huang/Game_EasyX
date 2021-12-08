#pragma once
#include "bullet.h"
#include "role.h"
#include <mmsystem.h>
#include <Windows.h>
#include <conio.h>

enum inputkey {
  NO_KEY,
  UP_KEY,
  DOWN_KEY,
  LEFT_KEY,
  RIGHT_KEY,
  UP2_KEY,
  DOWN2_KEY,
  LEFT2_KEY,
  RIGHT2_KEY,
  SPACE_KEY
};
extern bool presskey[50];
extern int myinputkey;
extern bool press;

extern clock_t bullet_time1, bullet_time2;

void initkey();
void getorder();
