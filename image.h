#pragma once
#include <graphics.h>
#include <time.h>

struct Gameimage {
	IMAGE background1;
	IMAGE background2[2];
	IMAGE background3[2];

	IMAGE img_role[3];
	IMAGE img_role_left[3];

	IMAGE bullet[2];
	IMAGE bullet_left[2];

	IMAGE hit[2];
};

extern struct Gameimage gameimage;

typedef struct showimage {
	int x;
	int y;
	clock_t statrtime;
	IMAGE* showimage1;
	IMAGE* showimage2;
	int endtime;
	struct showimage* next;
} imagelink;

void initimagelinks();
void addimage(int x, int y, int endtime, IMAGE* image1, IMAGE* image2);
void updataimage();