#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

static struct Scores {
    int p1score = 0;
    int p2score = 0;
} score_data;

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
        // Visuals
        SDL_Rect ball = { 0, 0, 30, 30 };
        SDL_Surface* ballImg = NULL;
        SDL_Texture* t_ball = NULL;
        SDL_Surface* fieldImg = NULL;
        SDL_Texture* t_field = NULL;
        SDL_Surface* player1Load = NULL;
        Player1 player1;
        SDL_Surface* player2Load = NULL;
        Player2 player2;

        // Scoring
        TTF_Font* SansFont = NULL;
        SDL_Color Black = { 0, 0, 0 };
        SDL_Surface* p1ScoreSurface = NULL;
        SDL_Texture* p1ScoreTexture = NULL;
        SDL_Rect p1ScoreDisplay = { 150, 50, 100, 100 };
        SDL_Surface* p2ScoreSurface = NULL;
        SDL_Texture* p2ScoreTexture = NULL;
        SDL_Rect p2ScoreDisplay = { 550, 50, 100, 100 };
        int p1Score = 0;
        int p2Score = 0;
        std::string p1Display = "";
        std::string p2Display = "";

        // Audio
        //Mix_Music* gameMusic;
        //Mix_Chunk* ballHit;
        //Mix_Chunk* p1Goal;
        //Mix_Chunk* p2Goal;

    public:
        // Functions
        void init(SDL_Renderer* renderer);
        std::vector<std::string> messages;
        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);
};

#endif