#include "Shader.h"
#include "glad/glad.h"
#include <stdio.h>
#include "Utils.h"

namespace FelicoEngine {
	Shader::Shader(const char* vertPath, const char* fragPath) {
		createVertShader(vertPath);
		createFragShader(fragPath);
		createProgram();
	}

	Shader::~Shader() {
		glDeleteShader(m_fragShader);
		glDeleteShader(m_vertShader);
		glDeleteProgram(m_ID);
	};

	void Shader::use() const {
		glUseProgram(m_ID);
	};

	void Shader::createVertShader(const char* vertPath) {
		GLint success;
		// Vert Shader
		m_vertShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vertCode = FelicoEngine::Utils::readFile(vertPath);
		const GLchar* vertShaderCode = vertCode.c_str();
		glShaderSource(m_vertShader, 1, &vertShaderCode, nullptr);
		glCompileShader(m_vertShader);
		glGetShaderiv(m_vertShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint logLength;
			glGetShaderiv(m_vertShader, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetShaderInfoLog(m_vertShader, logLength, nullptr, &log[0]);
			printf("Vertex shader compile error:\n%s\n", log.c_str());
		}
	}

	void Shader::createFragShader(const char* fragPath) {
		GLint success;
		// Frag Shader 
		m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragCode = FelicoEngine::Utils::readFile(fragPath);
		const GLchar* fragShaderCode = fragCode.c_str();
		glShaderSource(m_fragShader, 1, &fragShaderCode, nullptr);
		glCompileShader(m_fragShader);
		glGetShaderiv(m_fragShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint logLength;
			glGetShaderiv(m_fragShader, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetShaderInfoLog(m_fragShader, logLength, nullptr, &log[0]);
			printf("Fragment shader compile error:\n%s\n", log.c_str());
		}
	}

	void Shader::createProgram() {
		GLint success;
		// Program & Link
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, m_vertShader);
		glAttachShader(shaderProgram, m_fragShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLint logLength;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetProgramInfoLog(shaderProgram, logLength, nullptr, &log[0]);
			printf("Shader program link error:\n%s\n", log.c_str());
		}
		m_ID = shaderProgram;
	}
}