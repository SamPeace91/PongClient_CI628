#include "MyGame.h"

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
        std::cout << "Received: " << cmd << std::endl;
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;
        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;
        case SDLK_i:
            send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
            break;
        case SDLK_k:
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
            break;
    }
}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;
    ball.x = game_data.ballX;
    ball.y = game_data.ballY;
}

void MyGame::render(SDL_Renderer* renderer) {
    // Initialize PNG
    IMG_Init(IMG_INIT_PNG);

    // Field
    SDL_Surface* fieldImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Field.png");
    t_field = SDL_CreateTextureFromSurface(renderer, fieldImg);
    if (t_field == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", fieldImg, SDL_GetError); }
    // Player1
    SDL_Surface* player1Img = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player1.png");
    t_player1 = SDL_CreateTextureFromSurface(renderer, player1Img);
    if (t_player1 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player1Img, SDL_GetError); }
    // Player2
    SDL_Surface* player2Img = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Player2.png");
    t_player2 = SDL_CreateTextureFromSurface(renderer, player2Img);
    if (t_player2 == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", player2Img, SDL_GetError); }
    // Ball
    SDL_Surface* ballImg = IMG_Load("C:/Users/skyro/Desktop/UniFinalYear/MultiplayerDevelopment/PongClient/CI628/assets/Ball.png");
    t_ball = SDL_CreateTextureFromSurface(renderer, ballImg);
    if (t_ball == NULL) { printf("Unable to create texture from %s! SDL Error: %s\n", ballImg, SDL_GetError); }

    // Render PNG
    SDL_RenderCopy(renderer, t_field, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, t_player1, NULL, &player1);
    SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, t_player2, NULL, &player2);
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
    SDL_FreeSurface(player1Img);
    SDL_FreeSurface(player2Img);
    SDL_FreeSurface(ballImg);
}