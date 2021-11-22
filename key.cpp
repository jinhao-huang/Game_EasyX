#include "key.h"
#include "test.h"

int myinputkey;
bool presskey[50];
int kb;
bool wkb = false;

DWORD bullet_time1, bullet_time2;
DWORD bullet_time3, bullet_time4;

void initkey() {
	for (int i = 0; i < 50; i++) {
		presskey[i] = 0;
	}
}

void getorder() {
#if __TESTKEY__
	if (_kbhit()) {
		printf("%d", _getch());
	}
#endif

/*
	if (_kbhit())
	{
		kb = _getch();
		if (kb == 119 || kb == 87) {
			presskey[UP_KEY] = 1;
		}
		else if (kb == 224) {
			if (_getch() == 72) {
				presskey[UP2_KEY] = 1;
			}
		}
	}
*/


	/*
	if (GetKeyState('W') & 0x8000)
	{
		presskey[UP_KEY] = 1;
		printf("test");
	}	
	*/


	if ((GetAsyncKeyState('W') & 0x8000) && wkb == false)
	{
		wkb = true;
		presskey[UP_KEY] = 1;
	}

	if (GetAsyncKeyState('W') == 0) {
		wkb = false;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		presskey[DOWN_KEY] = 1;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		presskey[LEFT_KEY] = 1;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		presskey[RIGHT_KEY] = 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		presskey[DOWN2_KEY] = 1;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		presskey[LEFT2_KEY] = 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		presskey[RIGHT2_KEY] = 1;
	}
	if (GetAsyncKeyState('J') & 0x8000)
	{
		if ((bullet_time2 - bullet_time1) > gap_time)
		{
			addbullet(0);
			bullet_time1 = bullet_time2;
		}
	}
	bullet_time2 = GetTickCount();
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if ((bullet_time4 - bullet_time3) > gap_time)
		{
			addbullet(1);
			bullet_time3 = bullet_time4;
		}
	}
	bullet_time4 = GetTickCount();

#if __TEST__
	if (GetAsyncKeyState('X') & 0x8000) {
		printf("role2x:%lf role2y:%lf\n ", role[1].x, role[1].y);
	}
#endif
}