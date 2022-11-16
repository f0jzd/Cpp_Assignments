#define GLFW_INCLUDE_NONE

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

static const struct 
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    {-0.6f,-0.4f,1.f,0.f,0.f },
    {0.6f,-0.4f,0.f,1.f,0.f },
    {0.0f,0.6f,0.f,0.f,1.f },
};


//TODO read up on this stuff, this shader stuff
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

//TODO read up on this stuff, this shader stuff
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";





void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window,int key,int scancode, int action, int mods)
{
    if (GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}





int main(void)
{


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwSetKeyCallback(window, key_callback);


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);


    //TODO read up on this stuff, this shader stuff
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //TODO read up on this stuff, this shader stuff
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    //TODO read up on this stuff, this shader stuff
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    //TODO read up on this stuff, this shader stuff
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //TODO read up on this stuff, this shader stuff
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    //TODO read up on this stuff, this shader stuff
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(vertices[0]), (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(vertices[0]), (void*)(sizeof(float) * 2));

   

    

    //Returns the number of seconds since initialization, I guess this is kinda like that delta time calculation thing where the accumulated time minus the current time some thingy.
    double time = glfwGetTime();

    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        float ratio;
        int width, height;
        mat4x4 m, p, mvp;


        //Get the frame buffer size, of how many bitmaps can fit(?)
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        /* Render here */
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        //TODO read up on this stuff, this shader stuff
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        //The window has two rendering buffers.
        //The front buffer displays the currently loaded image, while the back buffer loads the next image, and then they swap, showing the new image and loading the next image.
        //The swap interval indicates how many frames to wait until swapping the buffers, commonly known as vsync.
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
       
        /* Poll for and process events */
        glfwPollEvents();

    }

    //When a window and context is no longer needed, destroy it.
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}