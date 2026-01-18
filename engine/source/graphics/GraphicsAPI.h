#pragma once
//this will serve as the centralized interface for rending operations
#include "GL/glew.h"
#include <memory>
#include <string>
namespace eng {

	class ShaderProgram;
	class Material;
	class GraphicsAPI {

	public:
		//this will receive the source code for vertex and fragment shader compile them, link them to shader program and return new shader program instance
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
	
		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
	};
}