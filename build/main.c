#include "SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>

#include "cfg.h"
#include "app.h"
#include "game.h"
#include "sprite.h"

int main(int argc, char *argv[])
{
	Config cfg;
	Application *app;
	Game *game;
	SDL_Event e;
	int running = 1;
	cfg.fullscreen = 0;
	cfg.width = 1280;
	cfg.height = 720;
	cfg.title = "SheePong";

	app = app_Init(&cfg);
	game = game_Init(app);

	while (running) {

		while (SDL_PollEvent(&e) > 0) {
			if (e.type == SDL_QUIT)
				running = 0;

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
			}
		}
		SDL_RenderCopy(app->renderer, game->paddle_left->t, NULL, game->paddle_left->r);
		SDL_RenderCopy(app->renderer, game->paddle_right->t, NULL, game->paddle_right->r);
		SDL_RenderCopyEx(app->renderer, game->ball->t, NULL, game->ball->r, game->ball->angle, 0, SDL_FLIP_NONE);
		game_Update(game, 0);
		app_BlitScreen(app);
	}
	app_Free(app);
	return 0;
}
