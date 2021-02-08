#include <iostream>
#include <glew.h>
#include <glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //If you press ESC and set windowShouldClose to True, the outer loop will close the application
    if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    std::cout<<"ESC"<<mode;
}

int main()
{
    if(!glfwInit())
        return -1;
    //Create window and context
    GLFWwindow* window = glfwCreateWindow(640, 480, "hello world", NULL, NULL);
    if(!window)
    {
        //Create failure will return NULL
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); //Register callback function
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); //Red
        glVertex3f(0, 1, 1);

        glColor3f(0, 1, 0); //Green
        glVertex3f(-1, -1, 0);

        glColor3f(0, 0, 1); //Blue
        glVertex3f(1, -1, 0);
        //End a drawing step
        glEnd();

        glBegin(GL_POLYGON);
        //Draw another trapezoid, you need to pay attention to the stroke order
        glColor3f(0.5, 0.5, 0.5); //Grey
        glVertex2d(0.5, 0.5);
        glVertex2d(1, 1);
        glVertex2d(1, 0);
        glVertex2d(0.5, 0);
        glEnd();


        /******Exchange buffer, update the content on the window******/
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
