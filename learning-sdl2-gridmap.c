#include <SDL2/SDL.h>

#define COLS 10
#define ROWS 10

int main() {
    int nx = 0, ny = 0;
    int arr[COLS][ROWS];
    FILE *fp = fopen("tile.txt", "r");
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL Texture denemesi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, -1);

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    SDL_Surface *spriteSurface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(spriteSurface, NULL, SDL_MapRGB(spriteSurface->format, 139, 69, 19));
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, spriteSurface);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(spriteSurface);
    
    SDL_Rect srcRect = {0, 0, 32, 32};
    SDL_Rect dstRect = {0, 0, 32, 32};
    SDL_Rect spriteRect = {0, 0, 32, 32};
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;
    
    for (int i = 0; i < COLS; i++) {
	for (int j = 0; j < ROWS; j++) {
	    if (arr[i][j] == 1) {
		dstRect.x = j * 32;
		dstRect.y = i * 32;
		SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
	    }
	}
    }

    while (running) {
	if (SDL_PollEvent(&event)) {
	    if (event.type == SDL_QUIT) {
		running = 0;
	    } else if (event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
		case SDLK_RIGHT: {
		    if (arr[ny][nx + 1] != 0) {
			spriteRect.x += 32;
			nx++;
		    }
		    break;
		}
		case SDLK_LEFT: {
		    if (arr[ny][nx - 1] != 0) {
			spriteRect.x -= 32;
			nx--;
		    }
		    break;
		}
		case SDLK_UP: {
		    if (arr[ny - 1][nx] != 0) {
			spriteRect.y -= 32;
			ny--;
		    }
		    break;
		}
		case SDLK_DOWN: {
		    if (arr[ny + 1][nx] != 0) {
			spriteRect.y += 32;
			ny++;
		    }
		    break;
		}
		}
	    }
	}
	SDL_RenderClear(renderer);
	for (int i = 0; i < COLS; i++) {
	    for (int j = 0; j < ROWS; j++) {
		fscanf(fp, "%d", &arr[i][j]);
		if (arr[i][j] == 1) {
		    dstRect.x = j * 32;
		    dstRect.y = i * 32;
		    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
		}
	    }
	}

	SDL_RenderCopy(renderer, sprite, NULL, &spriteRect);
	SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    fclose(fp);
    return 0;
}
