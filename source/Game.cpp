#include "Game.h"
#include <iostream>
#include <GLFW/glfw3.h>

bool Game::Init(){
    //vertex shader source code
    std::string vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;

    out vec3 vColor;
    
    void main() {
        vColor = color;
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
)";
    //fragment shader source code
    std::string fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 vColor;
    
    void main() {
        FragColor = vec4(vColor, 1.0);
    }
)";
    auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
    auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
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