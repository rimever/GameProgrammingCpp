#include "Shader.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <SDL_log.h>
#include <sstream>

Shader::Shader()
	: mVertexShader(0), mFragShader(0), mShaderProgram(0)
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	if (!CompileShader(vertName, GL_VERTEX_SHADER, this->mVertexShader)
		|| !CompileShader(fragName, GL_FRAGMENT_SHADER, this->mFragShader))
	{
		return false;
	}
	this->mShaderProgram = glCreateProgram();
	glAttachShader(this->mShaderProgram, this->mVertexShader);
	glAttachShader(this->mShaderProgram, this->mFragShader);
	glLinkProgram(this->mShaderProgram);

	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::Unload()
{
	glDeleteProgram(this->mShaderProgram);
	glDeleteShader(this->mVertexShader);
	glDeleteShader(this->mFragShader);
}

void Shader::SetActive()
{
	glUseProgram(this->mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	GLuint location = glGetUniformLocation(this->mShaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		auto contents = sstream.str();
		auto contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	glGetProgramiv(this->mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(this->mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
