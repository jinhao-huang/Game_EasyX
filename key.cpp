#include "key.h"
#include "test.h"

int myinputkey;
bool presskey[50];
int kb;
bool wkb = false;
bool press;

clock_t bullet_time1, bullet_time2;

void initkey() {
	for (int i = 0; i < 50; i++) {
		presskey[i] = 0;
	}
}

void getorder() {
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
	/* another way
	if ((GetAsyncKeyState('W') & 0x8000) && wkb == false)
	{
		wkb = true;
		presskey[UP_KEY] = 1;
	}
	if (GetAsyncKeyState('W') == 0) {
		wkb = false;
	}
	*/
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
		if (clock() - bullet_time1 > gap_time)
		{
			addbullet(0);
			bullet_time1 = clock();
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
 		if (clock() - bullet_time2 > gap_time)
		{
			addbullet(1);
			bullet_time2 = clock();
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		state = back;
		drawAlpha(&gameimage.backmenu, 0, 0);
	}
}