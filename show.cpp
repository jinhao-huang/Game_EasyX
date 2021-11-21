#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "show.h"
#include "role.h"

void showpoint() {
  static char hpmessage1[100];
  static char hpmessage2[100];
  sprintf_s(hpmessage1, "½ÇÉ«1HP£º%d", role[0].hp);
  sprintf_s(hpmessage2, "½ÇÉ«2HP£º%d", role[1].hp);
  outtextxy(100, 100, hpmessage1);
  outtextxy(1000, 100, hpmessage2);
}