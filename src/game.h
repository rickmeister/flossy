#ifndef GAME_H
#define GAME_H

#include "sprite.h"


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

void game_Update(Game *game, double delta);

void game_Free(Game *game);

#endif /* GAME_H */
