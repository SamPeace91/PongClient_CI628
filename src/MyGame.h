#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include <SDL_image.h>

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 200, 200, 20, 60 };
        SDL_Rect player2 = { 600, 600, 20, 60 };
        SDL_Rect ball = { 0, 0, 30, 30 };
        SDL_Texture* t_ball = NULL;
        SDL_Texture* t_field = NULL;
        SDL_Texture* t_player1 = NULL;
        SDL_Texture* t_player2 = NULL;

    public:
        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif