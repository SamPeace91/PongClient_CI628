#include "MyGame.h"

#include <SDL_image.h>

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
            //game_data.p1score = stoi(args.at(4));
            //game_data.p2score = stoi(args.at(5));
        }
    } else {
        std::cout << "Received: " << cmd << std::endl;
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
            Mix_PlayChannel(-1, p1scores, 0);
            if (p1scores == NULL) { printf("Unable to create audio from %s! SDL Error: %s\n", p1scores, SDL_GetError); }
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            Mix_PlayChannel(-1, ballHit, 0);
            break;
        case SDLK_i:
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            Mix_PlayChannel(-1, p2scores, 0);
            break;
        case SDLK_k:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            Mix_PlayChannel(-1, ballHit, 0);
            break;
    }
}

void MyGame::update() {
    player1.player1Img.y = game_data.player1Y;
    player2.player2Img.y = game_data.player2Y;
    ball.x = game_data.ballX;
    ball.y = game_data.ballY;
    //p1score = game_data.p1score;
    //p2score = game_data.p2score;
}

void MyGame::render(SDL_Renderer* renderer) {
    // Initialize PNG
    IMG_Init(IMG_INIT_PNG);

    // Field
    SDL_Surface* fieldImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Field.png");
    t_field = SDL_CreateTextureFromSurface(renderer, fieldImg);
    if (t_field == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", fieldImg, SDL_GetError); }
    // Player1
    SDL_Surface* player1Load = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player1.png");
    player1.t_player1 = SDL_CreateTextureFromSurface(renderer, player1Load);
    if (player1.t_player1 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player1Load, SDL_GetError); }
    // Player2
    SDL_Surface* player2Load = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player2.png");
    player2.t_player2 = SDL_CreateTextureFromSurface(renderer, player2Load);
    if (player2.t_player2 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player2Load, SDL_GetError); }
    // Ball
    SDL_Surface* ballImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Ball.png");
    t_ball = SDL_CreateTextureFromSurface(renderer, ballImg);
    if (t_ball == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", ballImg, SDL_GetError); }
    
    //printf("Player 1's score is: %i.\nPlayer 2's score is: %i.\n", p1score, p2score);

    // Render PNG
    SDL_RenderCopy(renderer, t_field, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, player1.t_player1, NULL, &player1.player1Img);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, player2.t_player2, NULL, &player2.player2Img);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, t_ball, NULL, &ball);
    SDL_RenderPresent(renderer);

    // Render Bats
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &player1);
    //SDL_RenderDrawRect(renderer, &player2);
    //SDL_RenderDrawRect(renderer, &ball);

    // Clear Surfaces
    SDL_FreeSurface(fieldImg);
    SDL_FreeSurface(player1Load);
    SDL_FreeSurface(player2Load);
    SDL_FreeSurface(ballImg);

    // Clear Audio
    Mix_FreeChunk(ballHit);
    Mix_FreeChunk(p1scores);
    Mix_FreeChunk(p2scores);
    //Mix_FreeMusic(gameMusic);

    // Quit Image
    IMG_Quit();
}