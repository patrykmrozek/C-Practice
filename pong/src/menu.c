#include "menu.h"

int checkMouseCollision(SDL_Event event, SDL_Rect* rect) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    //printf("MOUSE X: %d, MOUSE Y: %d\n", event.button.x, event.button.y);
    return (event.button.x >= rect->x
          && event.button.x <= rect->x+rect->w
          && event.button.y >= rect->y
          && event.button.y <= rect->y+rect->h);
}
  return 0;
}


int draw_menu(SDL_Surface* surface, SDL_Window* window, SDL_Event event, TTF_Font* font) {
    char playText[] = "PLAY";
    SDL_Surface* playTextSurface = TTF_RenderText_Solid(font, playText, TEXT_COLOR);
    SDL_Rect playTextRect = {(WIDTH/2)-playTextSurface->w,
                            (4*HEIGHT)/10,
                            playTextSurface->w,
                            playTextSurface->h
                          };		
    SDL_BlitSurface(playTextSurface, NULL, surface, &playTextRect);
    SDL_FreeSurface(playTextSurface);
    if (checkMouseCollision(event, &playTextRect)) {
 //     printf("MOUSE CLICKED ON PLAY!\n");
      return 1; // sets gamePlaying to 1 
  }
    
    char quitText[] = "QUIT";
    SDL_Surface* quitTextSurface = TTF_RenderText_Solid(font, quitText, TEXT_COLOR);
    SDL_Rect quitTextRect = {(WIDTH/2)-quitTextSurface->w,
                            (6*HEIGHT)/10,
                            quitTextSurface->w,
                            quitTextSurface->h
                          };		
    SDL_BlitSurface(quitTextSurface, NULL, surface, &quitTextRect);
    SDL_FreeSurface(quitTextSurface);
    if (checkMouseCollision(event, &quitTextRect)) {
   //   printf("MOSUSE CLICKED ON QUIT!\n");
      return 2; // sets gamePlaying to 2
  }
    SDL_UpdateWindowSurface(window);
    return 0;
}

