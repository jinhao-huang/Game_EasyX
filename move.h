#pragma once
#include <time.h>
#include "key.h"
#include "Settings.h"

enum role_margin
{
	role_lmargin = 80,
	role_rmargin = 80,
	role_umargin = 50,
	role_dmargin = 50
};

void move1(struct Role& role, clock_t time);
void move2(struct Role& role, clock_t time);

