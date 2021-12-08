#include <graphics.h>
#include <windows.h>
#include <Mmsystem.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include "key.h"
#include "move.h"
#include "Settings.h"
#include "role.h"
#include "image.h"
#include "bullet.h"
#include "show.h"
#include "image.h"
#include "control.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

int main () {
	ExMessage m;
	clock_t time;
	initgraph (width, height);
	initsettings();
	initimage();
	initgame();
	state = menu;
	
	while (1) {
		while (state == menu) {
			m = getmessage(EM_MOUSE);
			if (!m.lbutton) {
				press = false;
			}
			putimage(0, 0, &gameimage.start);
			if (playbgmusic == true)
				drawAlpha(&gameimage.check, 654, 98);
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 368 && m.y < 438 && !press) {
				press = true;
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 456 && m.y < 526 && !press) {
				press = true;
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
				loaddata();
			}
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 544 && m.y < 613 && !press) {
				press = true;
				closegraph();
				flushmessage(EM_MOUSE);
				return 0;
			}
			if (m.lbutton && m.x > 786 && m.x < 1033 && m.y > 66 && m.y < 124 && !press) {
				press = true;
				state = state_setting;
				flushmessage(EM_MOUSE);
				showsettings();
			}
			if (m.lbutton && m.x > 572 && m.x < 698 && m.y > 68 && m.y < 125 && !press) {
				press = true;
				if (playbgmusic == true) {
					playbgmusic = false;
				}
				else {
					playbgmusic = true;
				}
				flushmessage(EM_MOUSE);
			}
		}
		while (state == game) {
			time = clock();
			BeginBatchDraw();
			putimage(0, 0, &gameimage.background1);
			putimage(centerx(gameimage.background1, gameimage.background2[0]), 0, &gameimage.background2[0], SRCAND);
			putimage(centerx(gameimage.background1, gameimage.background2[1]), 0, &gameimage.background2[1], SRCINVERT);
			showpanel();
			showrole();

			move1(role[0], clock() - time);
			move2(role[1], clock() - time);
			updataimage();
			updatabullet();
			initkey();
			getorder();
			death();
			EndBatchDraw();
		}
		while (state == over) {
			m = getmessage(EM_MOUSE);
			if (!m.lbutton) {
				press = false;
			}
			PlaySound(NULL, NULL, SND_FILENAME | SND_PURGE);
			if (m.lbutton && m.x > 837 && m.y > 545 && m.y < 600 && !press) {
				press = true;
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x < 330 && m.y > 545 && m.y < 600 && !press) {
				press = true;
				state = menu;
				flushmessage(EM_MOUSE);
			}
		}
		while (state == back) {
			m = getmessage(EM_MOUSE);
			if (!m.lbutton) {
				press = false;
			}
			PlaySound(NULL, NULL, SND_FILENAME | SND_PURGE);
			if (m.lbutton && m.x > 837 && m.y > 545 && m.y < 600 && !press) {
				press = true;
				state = game;
				if(playbgmusic == true)
					PlaySound(_T("audio\\bgmusic.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x < 330 && m.y > 545 && m.y < 600 && !press) {
				press = true;
				state = menu;
				flushmessage(EM_MOUSE);
				savedata();
			}
		}
		while (state == state_setting) {
			m = getmessage(EM_MOUSE);
			if (!m.lbutton) {
				press = false;
			}
			if (m.lbutton && m.x > 679 && m.x < 1079 && m.y > 450 && m.y < 520 && !press) {
				press = true;
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x > 679 && m.x < 1079 && m.y > 566 && m.y < 635 && !press) {
				press = true;
				state = menu;
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 383 && m.x < 534 && m.y > 577 && m.y < 635 && !press) {
				press = true;
				changesetting(rolelives);
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 383 && m.x < 534 && m.y > 332 && m.y < 390 && !press) {
				press = true;
				changesetting(player1);
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 973 && m.x < 1124 && m.y > 332 && m.y < 390 && !press) {
				press = true;
				changesetting(player2);
				flushmessage(EM_MOUSE);
			}
		}
	}
	return 0;
}