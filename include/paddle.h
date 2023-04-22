#include <SDL2/SDL.h>

class Paddle
{
private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
    int m_rendererHeight{};
    int m_screenHeight{};

public:
    Paddle(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height, int screenHeight);

    void move(int verticalDistance);

    void render();

    int getPosX();
    
    int getPosY();

    int getPaddleHeight();

    int getPaddleWidth();
};