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
			putimage(0, 0, &gameimage.start);
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 368 && m.y < 438) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 456 && m.y < 526) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
				loaddata();
			}
			if (m.lbutton && m.x > 709 && m.x < 1109 && m.y > 544 && m.y < 613) {
				closegraph();
				return 0;
			}
			if (m.lbutton && m.x > 786 && m.x < 1033 && m.y > 66 && m.y < 124) {
				state = state_setting;
				showsettings();
			}
		}
		while (state == game) {
			if (playbgmusic == false) {
				PlaySound(_T("audio\\bgmusic.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
				playbgmusic = true;
			}
			time = clock();
			BeginBatchDraw();
			putimage(0, 0, &gameimage.background1);
			putimage(centerx(gameimage.background1, gameimage.background2[0]), 0, &gameimage.background2[0], SRCAND);
			putimage(centerx(gameimage.background1, gameimage.background2[1]), 0, &gameimage.background2[1], SRCINVERT);
			showpanel();
			showrole();
			initkey();
			getorder();
			move1(role[0], clock() - time);
			move2(role[1], clock() - time);
			updataimage();
			updatabullet();
			death();
			EndBatchDraw();
		}
		while (state == over) {
			PlaySound(NULL, NULL, SND_FILENAME | SND_PURGE);
			playbgmusic = false;
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 837 && m.y > 545 && m.y < 600) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x < 330 && m.y > 545 && m.y < 600) {
				state = menu;
				flushmessage(EM_MOUSE);
			}
		}
		while (state == back) {
			PlaySound(NULL, NULL, SND_FILENAME | SND_PURGE);
			playbgmusic = false;
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 837 && m.y > 545 && m.y < 600) {
				state = game;
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x < 330 && m.y > 545 && m.y < 600) {
				state = menu;
				flushmessage(EM_MOUSE);
				savedata();
			}
		}
		while (state == state_setting) {
			m = getmessage(EM_MOUSE);
			if (m.lbutton && m.x > 679 && m.x < 1079 && m.y > 450 && m.y < 520) {
				state = game;
				flushmessage(EM_MOUSE);
				startgame();
			}
			if (m.lbutton && m.x > 679 && m.x < 1079 && m.y > 566 && m.y < 635) {
				state = menu;
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 383 && m.x < 534 && m.y > 577 && m.y < 635) {
				changesetting(rolelives);
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 383 && m.x < 534 && m.y > 332 && m.y < 390) {
				changesetting(player1);
				flushmessage(EM_MOUSE);
			}
			if (m.lbutton && m.x > 973 && m.x < 1124 && m.y > 332 && m.y < 390) {
				changesetting(player2);
				flushmessage(EM_MOUSE);
			}
		}
	}
	return 0;
}