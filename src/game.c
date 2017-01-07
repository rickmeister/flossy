#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "game.h"
#include "sprite.h"
#include "app.h"

Game *game_Init(Application *app)
{
	Game *game;
	SDL_Surface *img;
	float x, y;
	float rnd;

	srand(time(NULL));
	rnd = rand() % 360;
	printf("Random number: %5.2f\n", rnd);
	game = malloc(sizeof(*game));

	IMG_Init(IMG_INIT_PNG);

	game->app = app;

	img = IMG_Load("assets/image/sheep.png");
	game->ball = sprite_Create(app->renderer, img);
	game->ball->x = app->wndWidth/2 - game->ball->r->w/2;
	game->ball->y = app->wndHeight/2 - game->ball->r->h/2;
	sprite_SetPosition(game->ball, game->ball->x, game->ball->y);
	game->ball->angle = rnd;
	game->ball->speed = 1.0;
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

void game_BallBounce(Sprite *ball, float d)
{
	ball->angle += d;
	if (ball->angle > 360)
		ball->angle -= 360;
}

int game_Intersects(SDL_Rect *a, SDL_Rect *b)
{
	if (a->x < b->x+b->w && a->x+a->w > b->x && a->y < b->y+b->h && a->y+a->h > b->y)
		return 1;
	return 0;
}

int game_InBounds(SDL_Rect *a)
{
	if (a->x < 0 || a->x+a->h > 1280 || a->y < 0 || a->y+a->h > 720) {
		return 0;
	}
	return 1;
}

void game_UpdateBall(Game *game)
{
	Sprite *ball = game->ball;
	float newx, newy, rad;

	if (game_Intersects(ball->r, game->paddle_left->r)) {
		sprintf(dbg_text, "Sheep collided with left paddle: %5.2f : %5.2f", ball->x, ball->y);
		game_BallBounce(ball, 180);
	} else if (game_Intersects(ball->r, game->paddle_right->r)) {
		sprintf(dbg_text, "Sheep collided with right paddle: %5.2f : %5.2f", ball->x, ball->y);
		game_BallBounce(ball, 180);
	}

	if (!game_InBounds(ball->r)) {
		game_BallBounce(ball, 90);
	}

	rad = 3.14159265359/180 * ball->angle;
	newx = ball->speed * cos(rad);
	newy = ball->speed * sin(rad);
	ball->x += newx;
	ball->y += newy;

}
void game_Update(Game *game, SDL_Event *e, double delta)
{
	if (e->type == SDL_MOUSEMOTION) {
		game->paddle_left->y = e->motion.y;
		sprite_Update(game->paddle_left);
	}
	game_UpdateBall(game);
	sprite_Update(game->ball);
}

void game_Free(Game *game)
{
	sprite_Destroy(game->paddle_left);
	sprite_Destroy(game->paddle_right);
	sprite_Destroy(game->ball);
	free(game);
}
