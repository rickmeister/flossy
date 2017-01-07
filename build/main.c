#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	TTF_Font *font;
	SDL_Surface *text;
	SDL_Texture *t;
	SDL_Color color;
	cfg.fullscreen = 0;
	cfg.width = 1280;
	cfg.height = 720;
	cfg.title = "SheePong";
	sprintf(dbg_text, "SheePong");
	app = app_Init(&cfg);
	game = game_Init(app);

	TTF_Init();
	font = TTF_OpenFont("assets/font/opensans.ttf", 20);
	color.a = 0xff;
	color.r = 0xff;
	color.g = 0xff;
	color.b = 0xff;

	while (running) {

		while (SDL_PollEvent(&e) > 0) {
			if (e.type == SDL_QUIT)
				running = 0;

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
			}
		}
		SDL_RenderClear(app->renderer);
		game_Update(game, &e, 0);
		text = SDL_CreateRGBSurface(0, 1280, 20, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		text = TTF_RenderText_Blended(font, dbg_text, color);
		t = SDL_CreateTextureFromSurface(app->renderer, text);
		SDL_RenderCopy(app->renderer, game->paddle_left->t, NULL, game->paddle_left->r);
		SDL_RenderCopy(app->renderer, game->paddle_right->t, NULL, game->paddle_right->r);
		SDL_RenderCopyEx(app->renderer, game->ball->t, NULL, game->ball->r, game->ball->angle, 0, SDL_FLIP_NONE);
		SDL_RenderCopy(app->renderer, t, NULL, &text->clip_rect);
		SDL_FreeSurface(text);
		SDL_DestroyTexture(t);
		app_BlitScreen(app);
	}
	app_Free(app);
	return 0;
}
