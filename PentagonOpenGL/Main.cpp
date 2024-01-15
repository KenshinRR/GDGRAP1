#include <GLFW/glfw3.h>
#include <cmath>

#define PI 3.14159265

int main(void)
{
    //initialize
    GLFWwindow* window;

    double conv = PI / 180;
    double radius = 0.8;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Reblando, Kenshin R.", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Drawing stuff */
        glBegin(GL_POLYGON);

        for (int point_index = 0, angle = 90; point_index < 5; point_index++, angle += 72)
        {
            glVertex2d(radius * cos(angle * conv), radius * sin(angle * conv));
        }

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}