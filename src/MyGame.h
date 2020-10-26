#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

#include <SDL_mixer.h>

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
    //int p1score = 0;
    //int p2score = 0;
} game_data;

class MyGame;

class Player1 {
    friend class MyGame;

    private:
        SDL_Rect player1Img = { 200, 200, 20, 60 };
        SDL_Texture* t_player1 = NULL;
};

class Player2 {
    friend class MyGame;

    private:
        SDL_Rect player2Img = { 600, 600, 20, 60 };
        SDL_Texture* t_player2 = NULL;
};

class MyGame {
    friend class Player1;
    friend class Player2;

    private:
        SDL_Rect ball = { 0, 0, 30, 30 };
        SDL_Texture* t_ball = NULL;
        SDL_Texture* t_field = NULL;
        Player1 player1;
        Player2 player2;
        //int p1score;
        //int p2score;
        //Mix_Music* gameMusic = Mix_LoadMUS("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/GameMusic.wav");
        Mix_Chunk* ballHit = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Football.wav");
        Mix_Chunk* p1scores = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/P1Goal.wav");
        Mix_Chunk* p2scores = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/P2Goal.wav");

    public:
        std::vector<std::string> messages;
        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif