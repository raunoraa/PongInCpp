#include "../include/ball.h"
#include "ball.h"


Ball::Ball() {
    m_x = 640;
    m_y = 360;
    m_width = 20;
    m_height = 20;
    m_velocityX = 1;
    m_velocityY = 1;
}

void Ball::Move() {
    m_x += m_velocityX;
    m_y += m_velocityY;
    CheckWallCollisions();
    CheckPaddleCollisions();
}

void Ball::Center(){
    m_x = m_SCREEN_WIDTH/2;
    m_y = m_SCREEN_HEIGHT/2;
}

void Ball::Draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_width;
    rect.h = m_height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::getPaddleHit(){
    return m_PADDLEHIT;
}

bool Ball::getWallHit()
{
    return m_WALLHIT;
}

void Ball::CheckPaddleCollisions() {

    // Check collision with left paddle
    if (m_x == m_leftPaddlePosX + m_leftPaddleWidth && (m_y + m_height >= m_leftPaddlePosY && m_y <= m_leftPaddlePosY + m_leftPaddleHeight))
    {
        m_PADDLEHIT = true;

        //x kiirust on vaja ainult vastupidiseks muuta 
        //(igaks juhuks lisame palli x positsioonile ka 1, et mitu korda siia if harusse kokkupuutel paddle'iga ei jõutaks)
        m_x = m_leftPaddlePosX + m_leftPaddleWidth + 1;
        m_velocityX = -m_velocityX;

        //muudame palli y kiirust vastavalt sellele, kuhu pall paddle'il maandus (annab mängijale rohkem kontrolli palli üle)
        //vaatame, kaugel on palli keskpunkt paddle'i keskpunktist
        //normaliseerime saadud kauguse lõiku [-2,2] (et kiirused liiga suureks ei läheks)
        int unnormalized = m_y + m_height/2 - m_leftPaddlePosY - m_leftPaddleHeight/2;
        int normalized = unnormalized / (m_leftPaddleHeight/5); //5 on saadud proovimise teel (sedasi tundus põrkamine kõige loogilisem)
        //teeme nii, et vertikaalne kiirus ei läheks üle 2 ega alla -2
        m_velocityY = normalized; 
        if (m_velocityY < -2)
        {
            m_velocityY = -2;
        }

        if (m_velocityY > 2)
        {
            m_velocityY = 2;
        }

    }
    

    // Check collision with right paddle
    else if (m_x + m_width == m_rightPaddlePosX && (m_y + m_height >= m_rightPaddlePosY && m_y <= m_rightPaddlePosY + m_rightPaddleHeight))
    {                
        /* Siia tuleb mingi targem loogika, et paddle abil saaks kontrollida palli liikumist */
        m_x = m_rightPaddlePosX - m_width - 1;
        m_velocityX = -m_velocityX;

        m_PADDLEHIT = true;

        //muudame palli y kiirust vastavalt sellele, kuhu pall paddle'il maandus (annab mängijale rohkem kontrolli palli üle)
        //vaatame, kaugel on palli keskpunkt paddle'i keskpunktist
        //normaliseerime saadud kauguse lõiku [-2,2] (et kiirused liiga suureks ei läheks)
        int unnormalized = m_y + m_height/2 - m_rightPaddlePosY - m_rightPaddleHeight/2;
        int normalized = unnormalized / (m_rightPaddleHeight/5); //5 on saadud proovimise teel (sedasi tundus põrkamine kõige loogilisem)
        //teeme nii, et vertikaalne kiirus ei läheks üle 2 ega alla -2
         m_velocityY = normalized;   
        if (m_velocityY < -2)
        {
            m_velocityY = -2;
        }

        if (m_velocityY > 2)
        {
            m_velocityY = 2;
        }

    } 

    else
    {
        m_PADDLEHIT = false;
    }
    

}

void Ball::CheckWallCollisions() {



    // Check collision with top wall
    if (m_y <= 0) {
        m_WALLHIT = true;
        m_velocityY = -m_velocityY;
    }
    // Check collision with bottom wall
    else if (m_y + m_height >= m_SCREEN_HEIGHT) {
        m_WALLHIT = true;
        m_velocityY = -m_velocityY;
    }
    else
    {
        m_WALLHIT = false; //ülemist ega alumist seina sel juhul hetkel ei puutu
    }
    

    //pall on paremal pool paremat paddle'it, vasak mängija saab punkti
    if (m_x + m_width >= m_SCREEN_WIDTH) {
        m_leftScores = true;
    }

    //pall on vasakul pool vasakut paddle'it, parem mängija saab punkti
    if (m_x <= 0) {
        m_rightScores = true;
    }
}

void Ball::setLeftPaddlePosX(int x)
{
    m_leftPaddlePosX = x;
}

void Ball::setLeftPaddlePosY(int y)
{
    m_leftPaddlePosY = y;
}

void Ball::setLeftPaddleHeight(int h)
{
    m_leftPaddleHeight = h;
}

void Ball::setLeftPaddleWidth(int w)
{
    m_leftPaddleWidth = w;
}

void Ball::setRightPaddlePosX(int x)
{
    m_rightPaddlePosX = x;
}

void Ball::setRightPaddlePosY(int y)
{
    m_rightPaddlePosY = y;
}

void Ball::setRightPaddleHeight(int h)
{
    m_rightPaddleHeight = h;
}

void Ball::setScreenWidth(int w)
{
    m_SCREEN_WIDTH = w;
}

void Ball::setScreenHeight(int h)
{
    m_SCREEN_HEIGHT = h;
}

bool Ball::getLeftScoresFlag()
{
    return m_leftScores;
}

bool Ball::getRightScoresFlag()
{
    return m_rightScores;
}

void Ball::resetScoreFlags()
{
    m_leftScores = false;
    m_rightScores = false;
}

void Ball::initializeVelocitiesMoveLeft()
{
    m_velocityY = -1;
    m_velocityX = -1;
}

void Ball::initializeVelocitiesMoveRight()
{
    m_velocityY = -1;
    m_velocityX = 1;
}
