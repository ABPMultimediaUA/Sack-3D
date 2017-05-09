#include "../include/shader.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include<vector>
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);



 //Shader::Shader(){}

Shader::Shader(const std::string& fileName)
{
    //std::cout<<"hi"<<std::endl;
    m_program = glCreateProgram();
    //std::cout<<"baia baia "<<m_program<<std::endl;
    //	std::cout<<"'"<<fileName<<"'"<<std::endl;
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER); //Vertex shader
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"),GL_FRAGMENT_SHADER); //Fragment shader

    for(unsigned int i = 0; i< NUM_SHADERS;i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program,0, "position");
    glBindAttribLocation(m_program,1, "texCoord");
    glBindAttribLocation(m_program,2, "normal");
    glBindAttribLocation(m_program,3, "color");


    glLinkProgram(m_program);
    CheckShaderError(m_program,GL_LINK_STATUS,true,"Error: Program linking failed ");

    glValidateProgram(m_program);
    CheckShaderError(m_program,GL_VALIDATE_STATUS,true,"Error: Program is invalid ");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

}
Shader::~Shader()
{
     for(unsigned int i = 0; i< NUM_SHADERS;i++){
        glDetachShader(m_program,m_shaders[i]);
        glDeleteShader(m_shaders[1]);
     }

    glDeleteProgram(m_program);
}

void Shader::Bind(){


    glUseProgram(m_program);

}


 GLuint Shader::positionLocation(){
    return m_program;
}

void Shader::Update(const glm::mat4& transformi){
    glm::mat4 model =  transformi;

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);
}
/*
void Shader::Update(const glm::mat4& camera ){
    glm::mat4 model = camera;

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);
}
*/

static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr<< "Error: La creacion del Shader ha fallado"<<std::endl;
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader,GL_COMPILE_STATUS,false,"Error: Ha fallado la compilacion del shader ");


    return shader;
}

static std::string LoadShader(const std::string& fileName){
	std::ifstream file;

   // std::cout<<fileName<<std::endl;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open()){
		while(file.good()){
			getline(file, line);

			output.append(line + "\n");

		}
	//	std::cout<<"'"<<output<<"'"<<std::endl;
	}
	else{
		std::cerr<<"No se ha podido cargar el shader"<<fileName << std::endl;
	}
	return output;
}
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
	GLint success	=	0;
	GLchar error[1024]	=	{	0	};

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE){
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error),NULL,error);
		else
			glGetProgramInfoLog(shader, sizeof(error),NULL,error);
		std::cerr << errorMessage<<": '"<<error<<"'"<<std::endl;
		}
	}

