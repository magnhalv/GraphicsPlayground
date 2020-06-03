

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int ID;
    
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        unsigned int vertexId = compileShader(vertexPath, GL_VERTEX_SHADER);
        unsigned int fragmentId = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
        
        ID = glCreateProgram();
        glAttachShader(ID, vertexId);
        glAttachShader(ID, fragmentId);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
    }

    unsigned int compileShader(const char *path, int shaderType) {
        auto code = getShaderCode(path);
        auto buffer = code.c_str();
        unsigned int id = glCreateShader(shaderType);        
        glShaderSource(id, 1, &buffer, NULL);
        glCompileShader(id);
        checkCompileErrors(id, "SHADER");
        return id;
    }

    std::string getShaderCode(const char *path) {
        try {
            std::ifstream shaderFile;
            shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);        
            shaderFile.open(path);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            return shaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            throw e;
        }
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setMat4(const std::string &name, const glm::mat4 matrix) const {
        auto loc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif

