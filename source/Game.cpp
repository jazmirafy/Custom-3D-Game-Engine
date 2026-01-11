#include "Game.h"
#include <iostream>
#include <GLFW/glfw3.h>

bool Game::Init(){

	return true;

}
void Game::Update(float deltaTime){

	//get instance of input manager
	auto& input = eng::Engine::GetInstance().GetInputManager();
	if (input.IsKeyPressed(GLFW_KEY_A)) {
		std::cout << "the A button has been pressed " << std::endl;
	}


}
void Game::Destroy(){


}