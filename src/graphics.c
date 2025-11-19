#include "../include/mingen.h"

static void _graphics_error(int error, const char* description) { }

static void _graphics_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}

static void _graphics_framebuffer_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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

    // store our shader for future use
    fn->gfx.shader = sprogram;
}

static void _graphics_setup(FN* fn)
{
    // setup GLFW
    if (!glfwInit()) { }

    // capture GLFW errors
    glfwSetErrorCallback(_graphics_error);

    // create the GLFW window
    fn->gfx.window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!fn->gfx.window) { }
    glfwMakeContextCurrent(fn->gfx.window);

    // capture window input
    glfwSetKeyCallback(fn->gfx.window, _graphics_key_callback);

    // set our window resize callback
    glfwSetFramebufferSizeCallback(fn->gfx.window, _graphics_framebuffer_resize);

    // setup the openGL functions with GLAD
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // set our vsync to 60
    glfwSwapInterval(1);

    // compile our shaders
    _graphics_compile_shaders(fn);
}

static void _graphics_render(FN* fn)
{
    // and here we render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // to draw an object we have to set the correct shader
    glUseProgram(fn->gfx.shader);

    // loop over our current map chunks and draw their meshs
    for(int i = 0; i < fn->data.map->chunks->length; i++)
    {
        chunk* c = GET(fn->data.map->chunks, chunk, i);
        fn->chunk.draw(fn, c);
    }

    glfwSwapBuffers(fn->gfx.window);
    glfwPollEvents();
}

static void _graphics_unload(FN* fn)
{
    // get rid of the GLFW window and instance
    glfwDestroyWindow(fn->gfx.window);
    glfwTerminate();
}

//
//  GRAPHICS.C:  handles all of our openGL rendering
//

void _init_graphics(FN* fn)
{
    fn->gfx.setup = &_graphics_setup;
    fn->gfx.render = &_graphics_render;
    fn->gfx.unload = &_graphics_unload;
}