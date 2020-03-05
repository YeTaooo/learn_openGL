//
//  main.cpp
//  12222
//
//  Created by 陶冶 on 03.03.20.
//  Copyright © 2020 陶冶. All rights reserved.
//
#include <iostream>
#include <glad/glad.h>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";


int main(int argc, const char * argv[]) {
    //initialize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //macos must have this code
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //create a window width hight return a GLFW object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
    if(!window){
        std::cout<<"Failed to create a GLFW window!"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
     glCompileShader(vertexShader);
     //detect if compile is successful
     int success;
     char infoLog[512];
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
     if(!success){
         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
         std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<std::endl;
     }
     //create fragment shader
     unsigned int fragmentShader;
     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
     glCompileShader(fragmentShader);
     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
     if(!success){
         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
         std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<std::endl;
     }
    
     //link shader to the program
     unsigned int shaderProgram;
     shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
     glLinkProgram(shaderProgram);
     glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
     if(!success){
         glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
         std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED"<<std::endl;
     }
     glDeleteShader(vertexShader);
     glDeleteShader(fragmentShader);
     
     
     //set size of rendering window, which we set the same as the size of the glfw window
     //glViewport(0, 0, 800, 600);
     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    float vertices2[]={
      -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
         -0.5f, -0.5f, 0.0f
    };
   
    
    
    
    unsigned int VBO1, VAO1,VBO2,VAO2;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    
    
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);//specify the type of the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);//specify the type of the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  
    

    while(!glfwWindowShouldClose(window)){
        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents(); //check if any events are triggered
 
    }
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glfwTerminate();
    
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, 800, 600);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
