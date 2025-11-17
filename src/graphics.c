#include "../include/mingen.h"

static void _graphics_error(int error, const char *description) { }

static void _graphics_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void _graphics_framebuffer_resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void _graphics_compile_shaders(FN *fn)
{
    // get our shader data from file
    char *fdata = fn->util.readfile("src/shader/fragment.shader");
    char *vdata = fn->util.readfile("src/shader/vertex.shader");

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

static void _graphics_setup(FN *fn)
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



    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &fn->gfx.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(fn->gfx.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 



    // here we loop until the window is closed somehow
    while (!glfwWindowShouldClose(fn->gfx.window))
    {
        // tick our game loop
        if (!fn->loop.isPaused) { fn->loop.tick(fn); }

        // process the window events
        glfwPollEvents();
    }
}

static void _graphics_render(FN *fn)
{
    // and here we render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // to draw an object we have to set the correct shader
    glUseProgram(fn->gfx.shader);
    // and then bind its VAO
    glBindVertexArray(fn->gfx.VAO); 

    // here loop over all the chunk objects and draw their mesh data
    // chunk *c = (chunk*) fn->data.map->chunks->data;
    // for(int i = 0; i < fn->data.map->chunks->length; i++)
    // {
    //     c += i;
    //     glBufferData(GL_ARRAY_BUFFER, c->mesh->vertices->size, c->mesh->vertices->data, GL_DYNAMIC_DRAW);
    // }


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // and unbind the VAO
    glBindVertexArray(0);

    glfwSwapBuffers(fn->gfx.window);
    glfwPollEvents();
}

static void _graphics_unload(FN *fn)
{
    // get rid of the GLFW window and instance
    glfwDestroyWindow(fn->gfx.window);
    glfwTerminate();
}

void _init_graphics(FN *fn)
{
    fn->gfx.setup = &_graphics_setup;
    fn->gfx.render = &_graphics_render;
    fn->gfx.unload = &_graphics_unload;
}