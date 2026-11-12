#include "Screen.h"
#include <stdio.h>

Screen* instance;
double fps = 60.0;

void Screen::startWindow() {

    if (!glfwInit())
        return;

    window = glfwCreateWindow(1920, 1080, "Running Simulation", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    return;

}

void Screen::hook(Simulation* simulationPTR) {

    this->simulationPTR = simulationPTR;
    this->simRenderer.hook(simulationPTR);
}
Simulation* simPTR = NULL;
void callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && simPTR != NULL) {
        simPTR->togglePause();
    }
}

SimulationRenderer* simRendererPTR;
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    simRendererPTR->zoom(3*yoffset / fps);
}

void Screen::mainLoop() {

    double lastFrameTime = glfwGetTime();

    Vec2D cursor;
    glfwGetCursorPos(window, &cursor.x, &cursor.y);
    
    while (!glfwWindowShouldClose(window))
    {
        double now = glfwGetTime();
        if (now - lastFrameTime < 1 / fps) {
            continue;
        }
        if (now - lastFrameTime > 1 / (fps * 0.75)) {
            //printf("Lagging behind! This frame took %.0lf ms out of the expected %.0lf\n", (now - lastFrameTime) * 1000, 1000.0 / fps);
        }
        /* Render here */
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        simRenderer.render(window);

        glfwSwapBuffers(window);
        simPTR = simulationPTR;
        glfwSetKeyCallback(window, callback);

        Vec2D tmp = cursor;
        glfwGetCursorPos(window, &cursor.x, &cursor.y);
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

            simRenderer.rotateCamera(-(cursor.y - tmp.y)/fps, (cursor.x - tmp.x)/fps);

        }

        simRendererPTR = &simRenderer;
        glfwSetScrollCallback(window, scrollCallback);

        glfwPollEvents();
        lastFrameTime = now;

    }
    glfwTerminate();
    simulationPTR->end();

}