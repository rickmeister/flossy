#include "SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>

#include "app.h"
#include "sprite.h"


/* Does NOT free the surface passed, caller must do it */
Sprite *sprite_Create(SDL_Renderer *r, SDL_Surface *s)
{
	Sprite *sprite;
	sprite = malloc(sizeof(*sprite));
	sprite->t = SDL_CreateTextureFromSurface(r, s);
	sprite->r = malloc(sizeof(SDL_Rect));
	sprite->r->w = s->w;
	sprite->r->h = s->h;
	return sprite;
}

void sprite_Destroy(Sprite *sprite)
{
	if (sprite->t)
		SDL_DestroyTexture(sprite->t);
	if (sprite->r)
		free(sprite->r);
	free(sprite);
}

void sprite_SetPosition(Sprite *sprite, float x, float y)
{
	sprite->x = x;
	sprite->y = y;
	sprite->r->x = (int)x;
	sprite->r->y = (int)y;
}

void sprite_Update(Sprite *sprite)
{
	sprite->r->x = (int)sprite->x;
	sprite->r->y = (int)sprite->y;
}
