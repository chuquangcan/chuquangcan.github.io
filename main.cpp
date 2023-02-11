#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>

using namespace std;
enum KEY
{
    KEYPRESSDEF,
    KEYPRESSUP,
    KEYPRESSRIGHT,
    KEYPRESSLEFT,
    KEYPRESSDOWN,
    TOTAL
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* currenttexture = NULL;
SDL_Texture* keypress[TOTAL];
SDL_Texture* bgtxt = NULL;
SDL_Texture* spidertxt = NULL;
SDL_Texture* tailtxt;
SDL_Event e;

SDL_Rect header{600, 300, 20, 20};
SDL_Rect tail[1001];
SDL_Rect spider;
int points=0;
int d = 0;

bool init();
SDL_Texture* loadimage(string path);
bool loadmedia();
void close();
void motion(int &check);
void spider_creating();
void direction(bool& quit, int& check);
void quitingandhunting_condition(bool& quit);

void display()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgtxt, NULL, NULL);
    SDL_RenderCopy(renderer, spidertxt, NULL, &spider);
    SDL_RenderCopy(renderer, currenttexture, NULL, &header);
    for (int i=1; i<=points; i++)
    {
        SDL_RenderCopy(renderer, tailtxt, NULL, &tail[i]);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
    int check=0;
    spider.w = 20; spider.h = 20;
    spider_creating();
    if (init())
    {
        if (loadmedia())
        {
            bool quit = false;
            while(!quit)
            {
                direction(quit, check);
                motion(check);
                quitingandhunting_condition(quit);

                display();
            }
            display();
        }
    }
    return 0;
}

void motion(int &check)
{
    switch(check)
    {
        case 1:
            header.y-=10;
            break;
        case 2:
            header.y+=10;
            break;
        case 3:
            header.x+=10;
            break;
        case 4:
            header.x-=10;
            break;
    }
    SDL_Delay(150);
}

void spider_creating()
{
    srand(time(0));
    spider.x= (rand()%118-0+1)*10;
    spider.y= (rand()%58-0+1)*10;
}
void direction(bool& quit, int& check)
{
    int oldx, oldy;
    int midx, midy;
    tail[0]=header;
    oldx=tail[0].x;
    oldy=tail[0].y;
    for (int i=1; i<=points; i++)
    {
        tail[i].w = 20;
        tail[i].h = 20;
        midx = tail[i].x;
        midy = tail[i].y;
        tail[i].x = oldx;
        tail[i].y = oldy;
        oldx = midx;
        oldy = midy;
    }
    while(SDL_PollEvent(&e)!=0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_UP:
                    currenttexture = keypress[KEYPRESSUP];
                    check = 1;
                    break;
                case SDLK_DOWN:
                    currenttexture = keypress[KEYPRESSDOWN];
                    check = 2;
                    break;
                case SDLK_RIGHT:
                    currenttexture = keypress[KEYPRESSRIGHT];
                    check = 3;
                    break;
                case SDLK_LEFT:
                    currenttexture = keypress[KEYPRESSLEFT];
                    check = 4;
                    break;
            }
        }
    }
}

void quitingandhunting_condition(bool& quit)
{
    for (int i=1; i<points; i++)
    {
        if ((header.x == tail[i].x) && (header.y == tail[i].y))
        {
            quit = true;
            break;
        }
    }
    if(header.x>=1180 || header.x<=0 || header.y>=580 || header.y<=0)
    {
        quit = true;
    }
    else if ((header.x == spider.x) && (header.y == spider.y))
    {
        points++;
        spider_creating();
    }
}


bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Init: " << SDL_GetError();
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "window: " << SDL_GetError();
            success =false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                cout << "render: " << SDL_GetError();
                success = false;
            }
            else
            {
                cout << IMG_Init(IMG_INIT_PNG);
            }
        }
    }
    return success;
}

SDL_Texture* loadimage(string path)
{
    SDL_Texture* newtxt = NULL;
    SDL_Surface* image = IMG_Load(path.c_str());
    if (image == NULL)
    {
        cout << "Image: " << SDL_GetError();
    }
    else
    {
        newtxt = SDL_CreateTextureFromSurface(renderer, image);
    }
    SDL_FreeSurface(image);
    return newtxt;
}

bool loadmedia()
{
    bool success = true;

    bgtxt = loadimage("bg.png");
    spidertxt = loadimage("moi-01.png");
    tailtxt = loadimage("tail.png");

    keypress[KEYPRESSUP] = loadimage("headerup.png");
    if (keypress[KEYPRESSUP] == NULL)
    {
        cout << "UP: " << SDL_GetError();
        success = false;
    }
    keypress[KEYPRESSDOWN] = loadimage("headerdown.png");
    if (keypress[KEYPRESSDOWN] == NULL)
    {
        cout << "Down: " << SDL_GetError();
        success = false;
    }
    keypress[KEYPRESSRIGHT] = loadimage("headerright.png");
    if (keypress[KEYPRESSRIGHT] == NULL)
    {
        cout << "right: " << SDL_GetError();
        success = false;
    }
    keypress[KEYPRESSLEFT] = loadimage("headerleft.png");
    if (keypress[KEYPRESSLEFT] == NULL)
    {
        cout << "left: " << SDL_GetError();
        success = false;
    }
    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyTexture(currenttexture);
    currenttexture = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}
