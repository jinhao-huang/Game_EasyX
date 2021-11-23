#include "show.h"

void showpanel() {
  Resize(&hp1, hpwidth * (role[0].hp / (double)initialhp), hpheight);
  drawAlpha(&gameimage.role_panel, 100, 35);
  drawAlpha(&hp1, 138, 54);
  Resize(&hp2, hpwidth * (role[1].hp / (double)initialhp), hpheight);
  drawAlpha(&gameimage.role_panel, 890, 35);
  drawAlpha(&hp2, 928, 54);

  outtextxy(142, 40, _T("Íæ¼Ò1"));
  outtextxy(933, 40, _T("Íæ¼Ò2"));
}