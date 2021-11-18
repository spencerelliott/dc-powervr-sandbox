#include "game.h"

Game::Game() : running(false) {

}

bool Game::IsRunning() {
    return false;
}

void Game::Init() {
    this->StartRunning();
}

void Game::StartRunning() {
    this->running = true;
}

void Game::StopRunning() {
    this->running = false;
}

void Game::Update() {

}

void Game::Draw() {

}

void Game::Cleanup() {

}

void Game::SetPlatform(Platform *new_platform) {
    this->platform = new_platform;
}