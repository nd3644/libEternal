#include "shader.h"
#include <iostream>
#include <fstream>

constexpr char fs[] =
"#version 430 core\n"

"in vec2 texCoord0;\n"
"in vec4 color0;\n"

"uniform sampler2D tex1;\n"

"out vec4 diffuseColor;\n"
"void main()\n"
"{\n"
"	if(textureSize(tex1, 0).x > 1) {\n"
"		diffuseColor = texture2D(tex1, texCoord0) * color0;\n"
"	}\n"
"	else {\n"
"		diffuseColor = color0;\n"
"	}\n"
"}";

constexpr char vs[] = 
"#version 430 core\n"

"layout(location = 0) in vec2 InPos;\n"
"layout(location = 1) in vec2 InTexCoord;\n"
"layout(location = 2) in vec4 InColor;\n"

"out vec2 texCoord0;\n"
"out vec4 color0;\n"

"void main()\n"
"{\n"
"	gl_Position = vec4(vec3(InPos.x - 1.0, 1.0 - InPos.y, 0), 1.0);\n"
"	texCoord0 = InTexCoord;\n"
"	color0 = InColor;\n"
"}";


Eternal::Shader::Shader() {
}

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

    std::cout << "---test---2" << std::endl;
    std::ifstream infile;
    std::string sline;
    std::string sVertex, sFragment;


    // Load shaders from file
    infile.open("shaders/basic_shader.vs");
    if(infile.fail() || infile.is_open() == false)
        std::cout << "couldn't open VS file" << std::endl;

    std::cout << "entering loop" << std::endl;
/*    while(!infile.eof()) {
        std::getline(infile, sline);
        sVertex += sline + "\n";
    }*/
    std::cout << "exited loop" << std::endl;
    infile.close();
    std::cout << std::endl;

    infile.open("shaders/basic_shader.fs");
/*    while(!infile.eof()) {
        std::getline(infile, sline);
        sFragment += sline + "\n";
    }*/
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

    sVertex = vs;
	p[0] = sVertex.c_str();
	lengths[0] = sVertex.length();

	glShaderSource(myShaders[Type::SHADER_VERTEX], 1, p, lengths);
	glCompileShader(myShaders[Type::SHADER_VERTEX]);

    GLchar buffer[256];
    GLsizei size;
	glGetShaderInfoLog(myShaders[Type::SHADER_VERTEX], 256, &size, buffer);

	// Compile frag shader
	const GLchar *ap[1];
	GLint alengths[1];

    sFragment = fs;
	ap[0] = sFragment.c_str();
	alengths[0] = sFragment.length();

	glShaderSource(myShaders[Type::SHADER_FRAGMENT], 1, ap, alengths);
	glCompileShader(myShaders[Type::SHADER_FRAGMENT]);
    glGetShaderInfoLog(myShaders[Type::SHADER_FRAGMENT], 256, &size, buffer);

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
