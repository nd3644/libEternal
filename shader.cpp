#include "shader.h"
#include <iostream>
#include <fstream>

Eternal::Shader::~Shader() {
    if(!bLoaded) {
        return;
    }
    glDetachShader(myProgram, myShaders[0]);
    glDetachShader(myProgram, myShaders[1]);


    glDeleteShader(myShaders[0]);
    glDeleteShader(myShaders[1]);
    glDeleteProgram(myProgram);
}

void Eternal::Shader::Initialize() {

    std::ifstream infile;
    std::string sline;
    std::string sVertex, sFragment;


    // Load shaders from file
    infile.open("shaders/basic_shader.vs");
    if(infile.fail())
        std::cout << "couldn't open VS file" << std::endl;

    while(!infile.eof()) {
        std::getline(infile, sline);
        sVertex += sline + "\n";
    }
    infile.close();
    std::cout << std::endl;

    infile.open("shaders/basic_shader.fs");
    while(!infile.eof()) {
        std::getline(infile, sline);
        sFragment += sline + "\n";
    }
    infile.close();

    /* Generate shaders */
    myProgram = glCreateProgram();

    myShaders[Type::SHADER_VERTEX] = glCreateShader(GL_VERTEX_SHADER);
    myShaders[Type::SHADER_FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
    if(myShaders[Type::SHADER_VERTEX] == 0)
        std::cout << "Couldn't create vertex shader" << std::endl;

    if(myShaders[Type::SHADER_FRAGMENT] == 0)
        std::cout << "Couldn't create frag shader" << std::endl;

	// Compile vert shader
    const GLchar *p[1];
	GLint lengths[1];

	p[0] = sVertex.c_str();
	lengths[0] = sVertex.length();

	glShaderSource(myShaders[Type::SHADER_VERTEX], 1, p, lengths);
	glCompileShader(myShaders[Type::SHADER_VERTEX]);
    std::cout << p[0] << std::endl;

    GLchar buffer[256];
    GLsizei size;
	glGetShaderInfoLog(myShaders[Type::SHADER_VERTEX], 256, &size, buffer);
    std::cout << buffer << std::endl;


	// Compile frag shader
	const GLchar *ap[1];
	GLint alengths[1];

	ap[0] = sFragment.c_str();
	alengths[0] = sFragment.length();
    std::cout << ap[0] << std::endl;


std::cout << "FRAGMENT: " << std::endl;
	glShaderSource(myShaders[Type::SHADER_FRAGMENT], 1, ap, alengths);
	glCompileShader(myShaders[Type::SHADER_FRAGMENT]);
    glGetShaderInfoLog(myShaders[Type::SHADER_FRAGMENT], 256, &size, buffer);
    std::cout << buffer << std::endl;

	// attach shaders
	glAttachShader(myProgram, myShaders[0]);
	glAttachShader(myProgram, myShaders[1]);

	glLinkProgram(myProgram);
	glValidateProgram(myProgram);

    bLoaded = true;
}

void Eternal::Shader::Bind() {
    glUseProgram(myProgram);
}
