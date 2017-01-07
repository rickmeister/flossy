#ifndef GAME_H
#define GAME_H

#include "sprite.h"

char dbg_text[256];

struct Application;

struct Game {
	struct Application *app;
	Sprite *paddle_left;
	Sprite *paddle_right;
	Sprite *ball;
	int score_left;
	int score_right;
	int balls_left;
};

typedef struct Game Game;

Game *game_Init(struct Application *app);

void game_Update(Game *game, SDL_Event *e, double delta);

void game_Free(Game *game);

#endif /* GAME_H */
