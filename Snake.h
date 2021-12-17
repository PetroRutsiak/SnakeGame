#include <iostream>
#include <vector>
#include "Apple.h"


enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Snake
{
private:
	std::vector<std::pair<int, int>> blocks;
	const int movement = 20;
	int dirX = 20, dirY ;
	
	Direction direction = Direction::RIGHT;
public:
	const int quadwidth = 20;
	const int quadheigth = 20;

	Snake()
	{
	}

	~Snake()
	{
		blocks.clear();
	}


	void init()
	{
	
		std::pair<int, int> pos_1;
		std::pair<int, int> pos_2;
		std::pair<int, int> pos_3;
		std::pair<int, int> pos_4;
		
		blocks.push_back(pos_1);
		blocks.push_back(pos_2);
		blocks.push_back(pos_3);
		blocks.push_back(pos_4);
	
		int startX = dirX * blocks.size();

		for (int i = 0; i < blocks.size(); i++)
		{

			blocks[i].first = startX;
			blocks[i].second = 20 ;

			startX -= dirX;
		}
	}

	void reset()
	{
		SDL_RenderPresent(gRenderer);
	}

	void render()
	{ 
		for (int i = 0; i < blocks.size(); i++)
		{

			SDL_Rect rect1 = { blocks[i].first, blocks[i].second, quadheigth, quadwidth };

			SDL_RenderFillRect(gRenderer, &rect1);
		}
	}

	void move( Apple* apple)
	{

		std::pair<int, int> pos;
		pos.first = blocks[0].first + dirX;

		pos.second = blocks[0].second + dirY;


		blocks.pop_back();
		blocks.insert(blocks.begin(), pos);

		if (pos.first == apple->getPosX() - 10 && pos.second == apple->getPosY() - 10)
		{
			apple->RandomPos();
			Grow();
		}

		if (isOverOfScreen(pos.first, pos.second ) || ckeckyourself(blocks[1].first, blocks[1].second))
		{
			SDL_Delay(10000);

			SDL_Quit();
		}
	}
	
	void sidemoves(SDL_Event& e)
	{
		//If a key was pressed
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				if (direction != Direction::UP && direction != Direction::DOWN)
				{
					direction = Direction::UP;
					dirY = -20;
					dirX = 0;
				}
				break;
			case SDLK_DOWN:
				if (direction != Direction::UP && direction != Direction::DOWN)
				{
					direction = Direction::DOWN;
					dirY = 20;
					dirX = 0;
				}
				break;
			case SDLK_LEFT:
				if (direction != Direction::LEFT && direction != Direction::RIGHT)
				{
					direction = Direction::LEFT;
					dirY = 0;
					dirX = -20;
				}
				break;
			case SDLK_RIGHT:
				if (direction != Direction::LEFT && direction != Direction::RIGHT)
				{
					direction = Direction::RIGHT;
					dirY = 0;
					dirX = 20;
				}
				break;
			}
		}
	}

	void Grow ()
	{
		
		std::pair<int, int> lastblock = blocks[blocks.size() - 1];
		std::pair<int, int> prelastblock = blocks[blocks.size() - 2];

		int difX = prelastblock.first - lastblock.first;
		int difY = prelastblock.second = lastblock.second;
		std::pair<int, int> newblock ;
		
			if (difX > 0)
			{
				newblock.first = lastblock.first - quadwidth;
				newblock.second = lastblock.second; 
			}
			if (difX < 0)
			{
				newblock.first = lastblock.first + quadwidth;
				newblock.second = lastblock.second;
			}
			if (difX == 0)
			{
				if (difY > 0)
				{
					newblock.first = lastblock.first;
					newblock.second = lastblock.second - quadheigth;
				}
				if (difY < 0)
				{
					newblock.first = lastblock.first;
					newblock.second = lastblock.second + quadheigth;
				}
			}
			blocks.push_back(newblock);
	}

	bool isOverOfScreen(int x, int y)
	{

		if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT || x < - quadwidth || y < - quadheigth)
		{
			return true;
		}
		return false;
	}


	bool ckeckyourself(int x, int y)
	{

		for (auto it =  2; it < blocks.size(); ++it)
		{
			if ( x >= blocks[it].first && y >= blocks[it].second && x < blocks[it].first + quadwidth && y < blocks[it].second + quadheigth )
			{
				return true;
			}
		}

		return false;
	}


};







