#include <SDL.h>
#include "Render.h"
#include "Snake.h"

int main(int argc, char* args[])
{
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
	
			//Main loop flag
			bool quit = false;
			Apple*  newapple = new Apple();
			Snake* newsnake = new Snake();
			
			newsnake->init();
			newapple->RandomPos();
			
			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);

				newsnake->render();
				newsnake->move(newapple);
				newsnake->sidemoves(e);
			
				SDL_Delay(80);
				SDL_SetRenderDrawColor(gRenderer, 150, 0, 0, 0);
			    
		        newapple->RenderFillCircle(gRenderer);
				
				SDL_RenderPresent(gRenderer);

			}
	}
	//Free resources and close SDL
	close();

	return 0;
}
