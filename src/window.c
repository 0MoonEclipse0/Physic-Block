/* window.c file for creating a window and rendering */

/* Includes */
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "util.h"

/* Defining shader-sources */
const char* fragShaderSource;
const char* vertShaderSource;

const char* readShader(const char* shaderfile,char buf[] ,int bufsize);

int CreateWindow(int width,int height, const char* title) {
    GLFWwindow *window;

    if (!glfwInit()) 
    {   
        printf("GLFW initialization failed\n");
        return -1;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {   
        printf("CreateWindow failed\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    char vertshadercontent[1028];
    vertShaderSource = readShader("shaders/shader.vert",vertshadercontent ,1028);
    char fragshadercontent[1028];
    fragShaderSource = readShader("shaders/shader.frag",fragshadercontent ,1028);

    /* Defining the verticies */
    float verts[] = {
         0.5f,  0.5f, 0.0f,  /* top right    */
         0.5f, -0.5f, 0.0f,  /* bottom right */
        -0.5f, -0.5f, 0.0f,  /* bottom left  */
        -0.5f,  0.5f, 0.0f   /* top left     */ 
    };
    /* Defining the indices */
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    /* Creating the VBO */
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /* Creating the VAO */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    /* Creating the EBO */
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    /* Binding and filling the VAO */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts),verts, GL_STATIC_DRAW);

    /* Binding and filling the EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

    /* Creating the vertex and fragment shaders */
    unsigned int vertShader;
    unsigned int fragShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Giving the vertex and fragment shaders a source */
    glShaderSource(vertShader, 1, &vertShaderSource, NULL);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(vertShader);
    glCompileShader(fragShader);

    /* Check if Shaders are compiled */
    int success;
    char infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        fprintf(stderr, "Shader compilation failed");
    }

    /* Creating the shader-program */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    /* Error checking for the shader-program */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ShaderProgram Failed");
    }

    /* Use the shader-program */
    glUseProgram(shaderProgram);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    /* Linking vertex-attributes */
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    /* Enabling the vertex-attributes */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts),verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    /* Rendering Loop */
    /*-------------------------------------------------------------*/
    while (!glfwWindowShouldClose(window))
    {   
        /* Rendering */
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}