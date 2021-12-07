#include "control.h"

int state;
bool playbgmusic;
char roleLives_str[10];
char buffer[1024];
char sbuffer[128]; //small buffer
char settingfilelocation[64] = "./setting.ini";
char datafilelocation[64] = "./data.ini";
LOGFONT myfont;
FILE* fp = NULL;
HWND hwnd;

void startgame() {
	clearbullet();
	myfont.lfHeight = 12;
	myfont.lfWeight = FW_NORMAL;
	settextstyle(&myfont);
	bullet_time1 = bullet_time2 = clock();
	role[0].lives = rolelives;
	role[1].lives = rolelives;
	role[0].direction = leftdire;
	role[1].direction = rightdire;
	reborn(role[0]);
	reborn(role[1]);
}

void initgame() {
	initbullet();
	initimagelinks();
	hpwidth = gameimage.hp.getwidth();
	hpheight = gameimage.hp.getheight();
	gettextstyle(&myfont);
	_tcscpy_s(myfont.lfFaceName, _T("黑体"));
	myfont.lfQuality = PROOF_QUALITY;
	settextstyle(&myfont);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "混乱大枪战");

	role[0].num = 0;
	role[1].num = 1;
	playbgmusic = false;

	return;
}

void initsettings() {
	GetPrivateProfileString("Setting", "Player1Name", "player1", player1, sizeof(player1), "./setting.ini");
	GetPrivateProfileString("Setting", "Player2Name", "player2", player2, sizeof(player2), "./setting.ini");
	rolelives = GetPrivateProfileInt("Setting", "RoleLives", 5, "./setting.ini");
	return;
	/*
	fopen_s(&fp, "settings.ini", "r");
	if (fp == NULL)
		return;
	else {
		fscanf_s(fp, "Player1:%s\n", player1, sizeof(player1));
		fscanf_s(fp, "Player2:%s\n", player2, sizeof(player2));
		fscanf_s(fp, "Rolelives:%d\n", &rolelives);
		fclose(fp);
		return;
	}	
	*/

}

void writesettings() {
	WritePrivateProfileString("Setting", "Player1Name", player1, settingfilelocation);
	WritePrivateProfileString("Setting", "Player2Name", player2, settingfilelocation);
	WritePrivateProfileString("Setting", "RoleLives", _itoa(rolelives, roleLives_str, 10), settingfilelocation);
	/*
	fopen_s(&fp, "settings.ini", "w");
	if (fp == NULL) {
		exit(0);
	}
	else {
		fprintf_s(fp, "Player1:%s\n", player1);
		fprintf_s(fp, "Player2:%s\n", player2);
		fprintf_s(fp, "Rolelives:%d\n", rolelives);
		fclose(fp);
		return;
	}	
	*/

}

void savedata() {
	hwnd = GetHWnd();
	int select;
	select = MessageBox(hwnd, "是否保存当前游戏进度？若已有存档，将会覆盖当前存档", _T("提示"), MB_OKCANCEL | MB_ICONWARNING);
	if (select == IDOK)
	{
		WritePrivateProfileString("Setting", "Exist", "yes", datafilelocation);

		WritePrivateProfileString("Role1", "lives", _itoa(role[0].lives, buffer, 10), datafilelocation);
		WritePrivateProfileString("Role1", "hp", _itoa(role[0].hp, buffer, 10), datafilelocation);
		WritePrivateProfileString("Role1", "direction", _itoa(role[0].direction, buffer, 10), datafilelocation);
		sprintf_s(buffer, "%.2f", role[0].x);
		WritePrivateProfileString("Role1", "x", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[0].y);
		WritePrivateProfileString("Role1", "y", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[0].vx);
		WritePrivateProfileString("Role1", "vx", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[0].vy);
		WritePrivateProfileString("Role1", "vy", buffer, datafilelocation);

		WritePrivateProfileString("Role2", "lives", _itoa(role[1].lives, buffer, 10), datafilelocation);
		WritePrivateProfileString("Role2", "hp", _itoa(role[1].hp, buffer, 10), datafilelocation);
		WritePrivateProfileString("Role2", "direction", _itoa(role[1].direction, buffer, 10), datafilelocation);
		sprintf_s(buffer, "%.2f", role[1].x);
		WritePrivateProfileString("Role2", "x", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[1].y);
		WritePrivateProfileString("Role2", "y", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[1].vx);
		WritePrivateProfileString("Role2", "vx", buffer, datafilelocation);
		sprintf_s(buffer, "%.2f", role[1].vy);
		WritePrivateProfileString("Role2", "vy", buffer, datafilelocation);

		bullet* p = bullethead;
		WritePrivateProfileString("Bullet", "x", "", datafilelocation);
		WritePrivateProfileString("Bullet", "y", "", datafilelocation);
		WritePrivateProfileString("Bullet", "player", "", datafilelocation);
		WritePrivateProfileString("Bullet", "direction", "", datafilelocation);
		while (p->next != NULL) {
			GetPrivateProfileString("Bullet", "x", "ERROR", buffer, sizeof(buffer), datafilelocation);
			sprintf_s(buffer, "%s %d", buffer, p->next->x);
			WritePrivateProfileString("Bullet", "x", buffer, datafilelocation);

			GetPrivateProfileString("Bullet", "y", "ERROR", buffer, sizeof(buffer), datafilelocation);
			sprintf_s(buffer, "%s %d", buffer, p->next->y);
			WritePrivateProfileString("Bullet", "y", buffer, datafilelocation);

			GetPrivateProfileString("Bullet", "player", "ERROR", buffer, sizeof(buffer), datafilelocation);
			sprintf_s(buffer, "%s %d", buffer, p->next->player);
			WritePrivateProfileString("Bullet", "player", buffer, datafilelocation);

			GetPrivateProfileString("Bullet", "direction", "ERROR", buffer, sizeof(buffer), datafilelocation);
			sprintf_s(buffer, "%s %d", buffer, p->next->direction);
			WritePrivateProfileString("Bullet", "direction", buffer, datafilelocation);

			p = p->next;
		}

		GetPrivateProfileString("Bullet", "player", "ERROR", buffer, sizeof(buffer), datafilelocation);
		sprintf_s(buffer, "%s %d", buffer, -1);
		WritePrivateProfileString("Bullet", "player", buffer, datafilelocation);
	}
}

void loaddata() {
	GetPrivateProfileString("Setting", "Exist", "ERROR", buffer, sizeof(buffer), datafilelocation);
	if (strcmp(buffer, "yes")) {
		hwnd = GetHWnd();
		MessageBox(hwnd, "没有可用存档!", _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}

	role[0].lives = GetPrivateProfileInt("Role1", "lives", rolelives, datafilelocation);
	role[0].hp = GetPrivateProfileInt("Role1", "hp", initialhp, datafilelocation);
	role[0].direction = GetPrivateProfileInt("Role1", "direction", rightdire, datafilelocation);
	sprintf_s(buffer, "%lf", bornx[0]);
	GetPrivateProfileString("Role1", "x", buffer, buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[0].x);
	sprintf_s(buffer, "%lf", borny[0]);
	GetPrivateProfileString("Role1", "y", buffer, buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[0].y);
	GetPrivateProfileString("Role1", "vx", "0", buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[0].vx);
	GetPrivateProfileString("Role1", "vy", "0", buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[0].vy);

	role[1].lives = GetPrivateProfileInt("Role2", "lives", rolelives, datafilelocation);
	role[1].hp = GetPrivateProfileInt("Role2", "hp", initialhp, datafilelocation);
	role[1].direction = GetPrivateProfileInt("Role2", "direction", rightdire, datafilelocation);
	sprintf_s(buffer, "%lf", bornx[1]);
	GetPrivateProfileString("Role2", "x", buffer, buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[1].x);
	sprintf_s(buffer, "%lf", borny[1]);
	GetPrivateProfileString("Role2", "y", buffer, buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[1].y);
	GetPrivateProfileString("Role2", "vx", "0", buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[1].vx);
	GetPrivateProfileString("Role2", "vy", "0", buffer, sizeof(buffer), datafilelocation);
	sscanf_s(buffer, "%lf", &role[1].vy);

	char buffer_x[1024] = {}, buffer_y[1024] = {}, buffer_player[1024] = {}, buffer_direction[1024] = {};
	GetPrivateProfileString("Bullet", "x", "", buffer_x, sizeof(buffer_x), datafilelocation);
	GetPrivateProfileString("Bullet", "y", "", buffer_y, sizeof(buffer_y), datafilelocation);
	GetPrivateProfileString("Bullet", "player", "", buffer_player, sizeof(buffer_player), datafilelocation);
	GetPrivateProfileString("Bullet", "direction", "", buffer_direction, sizeof(buffer_direction), datafilelocation);

	int x = 0, y = 0, player = 0, direction = 0;
	do {
		sscanf_s(buffer_x, "%d %[^\n]", &x, buffer_x, sizeof(buffer_x));
		sscanf_s(buffer_y, "%d %[^\n]", &y, buffer_y, sizeof(buffer_y));
		sscanf_s(buffer_player, "%d %[^\n]", &player, buffer_player, sizeof(buffer_player));
		sscanf_s(buffer_direction, "%d %[^\n]", &direction, buffer_direction, sizeof(buffer_direction));
		if(player != -1)
			loadbullet(x, y, player, direction);
	} while (player != -1);
	return;
}

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}