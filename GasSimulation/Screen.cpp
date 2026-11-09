#include "Screen.h"
#include <stdio.h>

Screen* instance;

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

void Screen::mainLoop() {

    double fps = 60.0;
    double lastFrameTime = glfwGetTime();
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
        glfwPollEvents();
        lastFrameTime = now;

    }
    glfwTerminate();
    simulationPTR->end();

}