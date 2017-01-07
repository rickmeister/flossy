#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "sprite.h"
#include "app.h"

Game *game_Init(Application *app)
{
	Game *game;
	SDL_Surface *img;
	float x, y;
	game = malloc(sizeof(*game));

	IMG_Init(IMG_INIT_PNG);

	game->app = app;

	img = IMG_Load("assets/image/sheep.png");
	game->ball = sprite_Create(app->renderer, img);
	game->ball->x = app->wndWidth/2 - game->ball->r->w/2;
	game->ball->y = app->wndHeight/2 - game->ball->r->h/2;
	sprite_SetPosition(game->ball, game->ball->x, game->ball->y);
	SDL_FreeSurface(img);

	img = IMG_Load("assets/image/paddlel.png");
	game->paddle_left = sprite_Create(app->renderer, img);
	x = 0;
	y = app->wndHeight/2 - game->paddle_left->r->h/2;
	sprite_SetPosition(game->paddle_left, x, y);
	SDL_FreeSurface(img);

	img = IMG_Load("assets/image/paddler.png");
	game->paddle_right = sprite_Create(app->renderer, img);
	x = app->wndWidth - game->paddle_right->r->w;
	y = app->wndHeight/2 - game->paddle_right->r->h/2;
	sprite_SetPosition(game->paddle_right, x, y);
	SDL_FreeSurface(img);


	return game;
}

void game_Update(Game *game, double delta)
{

}

void game_Free(Game *game)
{
	sprite_Destroy(game->paddle_left);
	sprite_Destroy(game->paddle_right);
	sprite_Destroy(game->ball);
	free(game);
}
