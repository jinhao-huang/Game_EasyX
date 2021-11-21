#pragma once
#include <graphics.h>

struct Gameimage {
	IMAGE background1;
	IMAGE background2[2];
	IMAGE background3[2];

	IMAGE img_role[3];
	IMAGE img_role_left[3];

	IMAGE bullet[2];
	IMAGE bullet_left[2];


};

extern struct Gameimage gameimage;