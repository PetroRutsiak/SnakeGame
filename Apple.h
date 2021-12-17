class Apple

{
private:
	int posX ;
	int posY ;
	int width = 20;
    int height = 20;
public:
	int getPosX() { return posX; }
    int getPosY() { return posY; }

    Apple() { }

    int RenderFillCircle(SDL_Renderer* renderer)
    {
        int offsetx, offsety, d;
        int status;
        offsetx = 0;
        offsety = width/2;
        d = width/2 - 1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, posX - offsety, posY + offsetx,
                posX + offsety, posY + offsetx);
            status += SDL_RenderDrawLine(renderer, posX - offsetx, posY + offsety,
                posX + offsetx, posY + offsety);
            status += SDL_RenderDrawLine(renderer, posX - offsetx, posY - offsety,
                posX + offsetx, posY - offsety);
            status += SDL_RenderDrawLine(renderer, posX - offsety, posY - offsetx,
                posX + offsety, posY - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (10 - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }

        return status;
    }
	
    void RandomPos()
    {
        posX = rand() % (640/ width)*width;
        posY = rand() % (480 / height)*width;
        posX += 10;
        posY += 10;
    }

};

