#include "SDL2/SDL.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "app.h"
#include "cfg.h"


void app_Cleanup(Application *app)
{
	if (app->title)
		free(app->title);

	if (app->renderer)
		SDL_DestroyRenderer(app->renderer);

	if (app->window)
		SDL_DestroyWindow(app->window);
	SDL_Quit();
	free(app);
}

Application *app_Init(Config *cfg)
{
	Application *app;
	int result;
	app = malloc(sizeof(*app));
	app->wndWidth = cfg->width;
	app->wndHeight = cfg->height;
	app->title = malloc(strlen(cfg->title));
	strcpy(app->title, cfg->title);
	app->wndFlags = SDL_WINDOW_SHOWN;

	if (cfg->fullscreen)
		app->wndFlags = app->wndFlags | SDL_WINDOW_FULLSCREEN;

	result = SDL_Init(SDL_INIT_EVERYTHING);

	if (result < 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		app_Cleanup(app);
		return NULL;
	}

	app->window = SDL_CreateWindow(app->title, 0, 0, app->wndWidth, app->wndHeight, app->wndFlags);
	if (!app->window) {
		printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		app_Cleanup(app);
		return NULL;
	}

	app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if(!app->renderer) {
		printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		app_Cleanup(app);
		return NULL;
	}

	return app;
}

void app_Free(Application *app)
{
	app_Cleanup(app);
}

int app_Run(Application *app, int debug)
{
	SDL_Event e;
	int result = 1;

	if (SDL_PollEvent(&e) > 0) {
		if (e.type == SDL_QUIT)
			result = 0;
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE)
				result = 0;
		}
	}
	SDL_RenderClear(app->renderer);

	return result;
}


void app_BlitScreen(Application *app)
{
	SDL_RenderPresent(app->renderer);
}
