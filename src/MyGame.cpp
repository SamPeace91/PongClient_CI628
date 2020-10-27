#include "MyGame.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

void MyGame::init(SDL_Renderer* renderer) {
    // Initialize PNG
    IMG_Init(IMG_INIT_PNG);

    // Field
    fieldImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Field.png");
    t_field = SDL_CreateTextureFromSurface(renderer, fieldImg);
    if (t_field == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", fieldImg, SDL_GetError); }
    // Player1
    player1Load = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player1.png");
    player1.t_player1 = SDL_CreateTextureFromSurface(renderer, player1Load);
    if (player1.t_player1 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player1Load, SDL_GetError); }
    // Player2
    player2Load = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player2.png");
    player2.t_player2 = SDL_CreateTextureFromSurface(renderer, player2Load);
    if (player2.t_player2 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player2Load, SDL_GetError); }
    // Ball
    ballImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Ball.png");
    t_ball = SDL_CreateTextureFromSurface(renderer, ballImg);
    if (t_ball == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", ballImg, SDL_GetError); }

    // Clear Surfaces
    SDL_FreeSurface(fieldImg);
    SDL_FreeSurface(player1Load);
    SDL_FreeSurface(player2Load);
    SDL_FreeSurface(ballImg);
    
    // Initialize Text
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    SansFont = TTF_OpenFont("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/OpenSans-Regular.ttf", 24);
    if (!SansFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    // Initialize Audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error, couldn't initialise SDL audio");
        exit(5);
    }

    //gameMusic = Mix_LoadMUS("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/GameMusic.wav");
    //ballHit = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Football.wav");
    //p1Goal = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/P1Goal.wav");
    //p2Goal = Mix_LoadWAV("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/P2Goal.wav");
}

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } else {
        //std::cout << "Received: " << cmd << std::endl;
    }
    if (cmd == "SCORES") {
        if (args.size() == 2) {
            score_data.p1score = stoi(args.at(0));
            score_data.p2score = stoi(args.at(1));
        }
    }
    else {
        //std::cout << "Received: " << cmd << std::endl;
    }
    //Mix_PlayMusic(gameMusic, 3);
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            //Mix_PlayChannel(-1, p1Goal, 0);
            //if (p1Goal == NULL) { printf("Unable to create audio from %s! SDL Error: %s\n", p1Goal, SDL_GetError); }
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            //Mix_PlayChannel(-1, ballHit, 0);
            break;
        case SDLK_i:
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            //Mix_PlayChannel(-1, p2Goal, 0);
            break;
        case SDLK_k:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            //Mix_PlayChannel(-1, ballHit, 0);
            break;
    }
}

void MyGame::update() {
    player1.player1Img.y = game_data.player1Y;
    player2.player2Img.y = game_data.player2Y;
    ball.x = game_data.ballX;
    ball.y = game_data.ballY;
    p1Score = score_data.p1score;
    p2Score = score_data.p2score;
    p1Display = std::to_string(p1Score);
    p2Display = std::to_string(p2Score);
}

void MyGame::render(SDL_Renderer* renderer) {
    //printf("Player 1's score is: %i.\nPlayer 2's score is: %i.\n", p1Score, p2Score);

    // Update Score Texture
    p1ScoreSurface = TTF_RenderText_Solid(SansFont, p1Display.c_str(), Black);
    p1ScoreTexture = SDL_CreateTextureFromSurface(renderer, p1ScoreSurface);
    if (p1ScoreTexture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", p1ScoreSurface, SDL_GetError); }
    p2ScoreSurface = TTF_RenderText_Solid(SansFont, p2Display.c_str(), Black);
    p2ScoreTexture = SDL_CreateTextureFromSurface(renderer, p2ScoreSurface);
    if (p2ScoreTexture == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", p2ScoreSurface, SDL_GetError); }

    // Render Visuals
    SDL_RenderCopy(renderer, t_field, NULL, NULL);
    SDL_RenderCopy(renderer, player1.t_player1, NULL, &player1.player1Img);
    SDL_RenderCopy(renderer, player2.t_player2, NULL, &player2.player2Img);
    SDL_RenderCopy(renderer, t_ball, NULL, &ball);
    SDL_RenderCopy(renderer, p1ScoreTexture, NULL, &p1ScoreDisplay);
    SDL_RenderCopy(renderer, p2ScoreTexture, NULL, &p2ScoreDisplay);
    SDL_RenderPresent(renderer);

    // Clear Surfaces
    SDL_FreeSurface(p1ScoreSurface);
    SDL_FreeSurface(p2ScoreSurface);
    
    // Old Render Bats & Ball
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &player1);
    //SDL_RenderDrawRect(renderer, &player2);
    //SDL_RenderDrawRect(renderer, &ball);

    // Clear Audio
    //Mix_FreeChunk(ballHit);
    //Mix_FreeChunk(p1Goal);
    //Mix_FreeChunk(p2Goal);
    //Mix_FreeMusic(gameMusic);

    // Quit Image
    //IMG_Quit();
}