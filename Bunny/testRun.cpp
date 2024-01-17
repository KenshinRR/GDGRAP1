#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#define PI 3.14159265

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

int main(void)
{
    //initialize variables
    GLFWwindow* window;

    double conv = PI / 180;
    double radius = 0.8;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Reblando, Kenshin R.", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //defining the 3D object    
    std::string path = "3D/bunny.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    //get the EBO indices array
    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    //defining the "3D" triangle
    GLfloat vertices[]{
        //x     y   z
        0.0f, 0.5f, 0.0f, //first point
        -0.5f, -0.5f, 0.0f, //second point
        0.5f, -0.5f, 0.0f //third point
    };

    GLuint indices[]{
        0,1,2 //triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    //currently editing VAO = null
    glBindVertexArray(VAO); //after calling
    //currently editing VAO = VAO (or whatever is inside the parameter)

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);*/

    //glVertexAttribPointer(
    //    0, //0 position, 1 texture, 2 norms
    //    3, //means xyz
    //    GL_FLOAT, //what data type
    //    GL_FALSE,
    //    3 * (sizeof(float)),
    //    (void*)0
    //);

    //VAO <- VBO

    //currently editing VBO = VBO
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW);*/
    //currently editing VBO = EBO

    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * attributes.vertices.size(),
        &attributes.vertices[0],
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, //0 position, 1 texture, 2 norms
        3, //means xyz
        GL_FLOAT, //what data type
        GL_FALSE,
        3 * (sizeof(GL_FLOAT)),
        (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        mesh_indices.data(),
        GL_STATIC_DRAW);

    //VAO <- EBO

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Drawing stuff */
        /*glBegin(GL_POLYGON);
        
        for (int point_index = 0, angle = 90; point_index < 5; point_index++, angle+=72)
        {
            glVertex2d(radius * cos(angle * conv), radius * sin(angle * conv));
        }
            
        glEnd();*/

        /*glBegin(GL_QUADS);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();*/

        //bind the VAO to prep for drawing
        glBindVertexArray(VAO);
        //drawing
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}