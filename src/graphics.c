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

static void _graphics_compile_shaders(FN* fn)
{
    // get our shader data from file
    char* fdata = fn->util.readfile("src/shader/fragment.shader");
    char* vdata = fn->util.readfile("src/shader/vertex.shader");

    // have openGL compile the shaders
    unsigned int fshader, vshader;
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fshader, 1, (const GLchar**) &fdata, NULL); glCompileShader(fshader);
    glShaderSource(vshader, 1, (const GLchar**) &vdata, NULL); glCompileShader(vshader);

    // create a shader program and link our shaders to it
    unsigned int sprogram;
    sprogram = glCreateProgram();
    glAttachShader(sprogram, fshader);
    glAttachShader(sprogram, vshader);
    glLinkProgram(sprogram);

    // get rid of our temp shader data
    glDeleteShader(fshader); free (fdata);
    glDeleteShader(vshader); free (vdata);

    // store our shader program for future use
    fn->gfx.shader = sprogram;
}

//
//  SETUP:  called when program is started, it will setup our window,
//          the openGL callbacks, load GLAD, and compile our shaders
//

static void _graphics_setup(FN* fn)
{
    // setup GLFW
    if (!glfwInit()) { }

    // capture GLFW errors
    glfwSetErrorCallback(_graphics_error);

    // create the GLFW window
    fn->gfx.window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

    // make it the current context
    glfwMakeContextCurrent(fn->gfx.window);

    // set our window resize callback
    glfwSetFramebufferSizeCallback(fn->gfx.window, _graphics_framebuffer_resize);

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

static void _graphics_render(FN* fn)
{
    // and here we render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // to draw an object we have to set the correct shader
    glUseProgram(fn->gfx.shader);

    // loop over our current maps chunks and draw their meshs
    for(int i = 0; i < fn->data.map->chunks->length; i++)
    {
        chunk* c = GET(fn->data.map->chunks, chunk, i);
        fn->chunk.draw(fn, c);
    }
}

//
//  UNLOAD:  we call this before we close the window
//

static void _graphics_unload(FN* fn)
{
    glfwDestroyWindow(fn->gfx.window);
    glfwTerminate();
}

//
//  GRAPHICS.C:  handles all of our GLFW functions and openGL rendering
//

void _init_graphics(FN* fn)
{
    fn->gfx.setup = &_graphics_setup;
    fn->gfx.render = &_graphics_render;
    fn->gfx.unload = &_graphics_unload;
}