#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include <iostream>
namespace eng {

	std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(const std::string& vertexSource, const std::string fragmentSource) {

        //create shader in graphics card
        //compile vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderCStr = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
        glCompileShader(vertexShader);

        //check if vertex shader compilation was successful
        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        //if vertex shader compilation is unsuccessful, display the error
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
            return nullptr;
        }
        //compile fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSourceCStr = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
        glCompileShader(fragmentShader);

        //check if fragment shader compilation was successful
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
            return nullptr;
        }

        //combine vertex and fragment shaders into a single shader program
        //create obeject for shader program in the graphics card
        GLuint shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShader);
        glAttachShader(shaderProgramID, fragmentShader);
        glLinkProgram(shaderProgramID);

        //check link status check for errors
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
        //if there is an error when linking, display the error
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
            std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
            return nullptr;
        }

        //once the shader program has successfully linked we no longer need the individual shader objects
        // delete individual shader objects from gpu memory
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //after successful compilation and linking wrap the resulting program id into shader program object and return via make shared
        return std::make_shared<ShaderProgram>(shaderProgramID);

	}
    void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram) {

        //lets us bind shaders both directly and via unified graphics api class
        shaderProgram->Bind();
    }
}