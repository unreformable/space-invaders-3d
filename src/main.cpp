#include "Animation.hpp"
#include "Bitmap3D.hpp"
#include "CoordinateSystem.hpp"
#include "Utils.hpp"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "SDL2/SDL.h"

#include <cassert>
#include <iostream>



const char* vs_source =
    "#version 450 core\n"
    "layout(location = 0) in vec3 vPos;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProj;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uProj * uView * vec4(vPos, 1.0);\n"
    "}\0";

const char* fs_source =
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8);\n"
    "}\0";

int main()
{
    // SETUP
    const int window_w = 600;
    const int window_h = 800;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initalize SDL2" << std::endl;
        return 1;
    }
    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow("Space Invaders 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_OPENGL);
    assert(window != NULL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    assert(context != NULL);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    
    // V-sync on
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glViewport(0, 0, window_w, window_h);

    // SMALL INVADER
    Bitmap3D bitmap;
    bitmap.Load("../assets/bitmaps/small_invader");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();

    Animation animation;
    animation.CreateFromBitmap(bitmap);

    GLint success = GL_TRUE;
    GLchar info_log[512];
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetShaderInfoLog(vs, 512, NULL, info_log);
        std::cerr << "Could not compile vertex shader\n" << info_log << std::endl;
    }
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetShaderInfoLog(fs, 512, NULL, info_log);
        std::cerr << "Could not compile fragment shader\n" << info_log << std::endl;
    }
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
        std::cerr << "Could not link program\n" << info_log << std::endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    // CAMERA
    const glm::mat4 proj = glm::perspectiveRH(glm::radians(45.0f), static_cast<float>(window_w)/window_h, 0.1f, 100.0f);
    glProgramUniformMatrix4fv(program, glGetUniformLocation(program, "uProj"), 1, GL_FALSE, glm::value_ptr(proj));

    bool key_states[SDL_NUM_SCANCODES]{};
    glm::vec3 camera_pos = glm::vec3(5, 5, 20);
    float camera_pitch = 0;
    float camera_yaw = 0;

    // MAIN LOOP
    bool running = true;
    while(running == true)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            if(e.type == SDL_KEYDOWN)
            {
                key_states[e.key.keysym.scancode] = 1;

                if(e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
            }
            if(e.type == SDL_KEYUP)
            {
                key_states[e.key.keysym.scancode] = 0;
            }
            if(e.type == SDL_MOUSEMOTION)
            {
                camera_pitch -= e.motion.yrel * 0.004f;
                camera_yaw -= e.motion.xrel * 0.004f;

                camera_pitch = glm::clamp(camera_pitch, glm::radians(-89.0f), glm::radians(89.0f));
            }
        }

        const glm::vec3 camera_forward = glm::vec3(
            -glm::sin(camera_yaw),
             glm::sin(camera_pitch) * glm::cos(camera_yaw),
            -glm::cos(camera_pitch) * glm::cos(camera_yaw)
        );
        const glm::vec3 camera_right = glm::normalize(glm::cross(camera_forward, kWorldUp));

        const float speed = 0.1f;
        glm::vec3 camera_vel{};
        if(key_states[SDL_SCANCODE_W] == 1)         camera_vel += speed * camera_forward;
        if(key_states[SDL_SCANCODE_S] == 1)         camera_vel -= speed * camera_forward;
        if(key_states[SDL_SCANCODE_D] == 1)         camera_vel += speed * camera_right;
        if(key_states[SDL_SCANCODE_A] == 1)         camera_vel -= speed * camera_right;
        if(key_states[SDL_SCANCODE_SPACE] == 1)     camera_vel.y += speed;
        if(key_states[SDL_SCANCODE_LSHIFT] == 1)    camera_vel.y -= speed;
        camera_pos += camera_vel;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const glm::mat4 view = glm::lookAtRH(camera_pos, camera_pos + camera_forward, kWorldUp);
        glProgramUniformMatrix4fv(program, glGetUniformLocation(program, "uView"), 1, GL_FALSE, glm::value_ptr(view));
        glUseProgram(program);
        animation.Render(program, 0);

        SDL_GL_SwapWindow(window);

        const GLenum error_code = glGetError();
        if(error_code != GL_NONE)
        {
            std::cerr << "OpenGL error. Error code: " << std::hex << error_code << std::endl;
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}