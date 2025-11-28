#include "../include/mingen.h"

//
//  ERROR:  print any errors GLFW throws at us
//

static void _graphics_error(int error, const char* description) 
{ 
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

//
//  FRAMEBUFFER_RESIZE:  whenever the GLFW window is created or resized this gets called
//                       when this happens we need to tell openGL what our new viewport sizes are
//

static void _graphics_framebuffer_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//
//  COMPILE_SHADERS:  reads our shaders in /src/shader/ and compiles them for use in openGL
//

static void _graphics_compile_shaders()
{
    // get our shader data from file
    char* vdata = load("../../src/shader/vertex.shader");
    char* fdata = load("../../src/shader/fragment.shader");

    // have openGL compile the shaders
    unsigned int vshader, fshader;
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vshader, 1, (const GLchar**) &vdata, NULL); glCompileShader(vshader);
    glShaderSource(fshader, 1, (const GLchar**) &fdata, NULL); glCompileShader(fshader);

    GLint s1; glGetShaderiv(fshader, GL_COMPILE_STATUS, &s1);
    if (!s1) { char l[512]; glGetShaderInfoLog(fshader, 512, NULL, l); printf("Fragment Shader Failed:\n%s\n", l); }

    GLint s2; glGetShaderiv(vshader, GL_COMPILE_STATUS, &s2);
    if (!s2) { char l[512]; glGetShaderInfoLog(vshader, 512, NULL, l); printf("Vertex Shader Failed:\n%s\n", l); }

    // create a shader program and link our shaders to it
    unsigned int s;
    s = glCreateProgram();
    glAttachShader(s, vshader);
    glAttachShader(s, fshader);
    glLinkProgram(s);

    // Check for linking errors
    GLint s3; glGetProgramiv(s, GL_LINK_STATUS, &s3);
    if (!s3) { char l[512]; glGetProgramInfoLog(s, 512, NULL, l); printf("Shader Program Failed:\n%s\n", l); }

    // get rid of our temp shader data
    glDeleteShader(vshader); free (vdata);
    glDeleteShader(fshader); free (fdata);

    // store our shader program for future use
    fn.gfx.shader = s;
}

//
//  SETUP:  called when program is started, it will setup our window,
//          the openGL callbacks, load GLAD, and compile our shaders
//

static void _graphics_setup()
{
    // setup GLFW
    if (!glfwInit()) { }

    // capture GLFW errors
    glfwSetErrorCallback(_graphics_error);

    // create the GLFW window
    fn.gfx.window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);

    // make it the current context
    glfwMakeContextCurrent(fn.gfx.window);

    // set our window resize callback
    glfwSetFramebufferSizeCallback(fn.gfx.window, _graphics_framebuffer_resize);

    // setup the openGL functions with GLAD
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // set our vsync to 60
    glfwSwapInterval(1);

    // compile our shaders
    _graphics_compile_shaders(fn);
}

//
//  RENDER:  gets called every frame, this is what actually draws all of our shapes
//           to the window with openGL
//

static void _graphics_render()
{
    // and here we render
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // to draw an object we have to set the correct shader
    glUseProgram(fn.gfx.shader);

    glEnable(GL_DEPTH_TEST);

    // loop over our current maps chunks and draw their meshs
    // for(int i = 0; i < fn.data.map->chunks->count; i++)
    // {
    //     chunk* c = fn.list.get(fn.data.map->chunks, 0);
    //     fn.chunk.draw(c);
    // }

    static const float cubeVertices[] = {
        // positions       
    -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
    };

        unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),cubeVertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);

    // ---- Camera settings ----
    vec3 cameraPos    = {0.0f, 0.0f, 3.0f};
    vec3 target       = {0.0f, 0.0f, 0.0f};  // cube at origin
    vec3 up           = {0.0f, 1.0f, 0.0f};

    // Projection (45 FOV, aspect 800/600)
    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f/600.0f, 0.1f, 100.0f, projection);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(fn.gfx.shader);

        if (fn.input.A.pressed)
        {
            printf("hit");
            cameraPos[0] = 1.0f;
        }

        // VIEW matrix
        mat4 view;
        glm_lookat(cameraPos, target, up, view);

        // MODEL matrix (cube at 0,0,0)
        mat4 model;
        glm_mat4_identity(model);

        // MVP
        mat4 MVP;
        glm_mat4_mulN((mat4 *[]){&projection, &view, &model}, 3, MVP);

        int loc = glGetUniformLocation(fn.gfx.shader, "MVP");
        glUniformMatrix4fv(loc, 1, GL_FALSE, (const float*)MVP);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
}

//
//  UNLOAD:  we call this before we close the window
//

static void _graphics_unload()
{
    glfwDestroyWindow(fn.gfx.window);
    glfwTerminate();
}

//
//  GRAPHICS.C:  handles all of our GLFW functions and openGL rendering
//

void _init_graphics()
{
    fn.gfx.setup = &_graphics_setup;
    fn.gfx.render = &_graphics_render;
    fn.gfx.unload = &_graphics_unload;
}