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
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    unsigned int indices[]=
    {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
   
    
    
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//specify the type of the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //copy the user defined data into the bound buffer
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    //create vertex shader
    

    while(!glfwWindowShouldClose(window)){
        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every tim
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        
        glfwPollEvents(); //check if any events are triggered
 
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
