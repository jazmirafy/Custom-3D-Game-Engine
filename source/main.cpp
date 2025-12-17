#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
int main()
{
    //initialize library
    
    //if we failed to initialize the glfw library stop the program
    if (!glfwInit()) {
        return -1;
    }

    //let glfw know which open gl context is intended to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //attempt to create a window
    GLFWwindow* window = glfwCreateWindow(1200, 720, "Egypt's Game Engine", nullptr, nullptr);


    //check whether the window was successfully created
    
    // if failed notify the user, terminate the glfw library and exit the program
    if (window == nullptr) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //if the window was successfully created enter the main event loop

    //set window position
    //glfwSetWindowPos(window, -, -);

    //specifying which window our open gl context needs to be associated with
    glfwMakeContextCurrent(window);

    //if we fail to initialize glew library terminate the program
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    //vertex shader source code
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;
        
        out vec3 vColor;


        void main(){
            vColor = color;
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
    )";
    //create shader in graphics card
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //compile vertex shader
    const char* vertexShaderCstr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCstr, nullptr);
    glCompileShader(vertexShader);

    //check if vertex shader compilation was successful
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    //if vertex shader compilation is unsuccessful, display the error
    if (!success) {

        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    //fragment shader source code
    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        in vec3 vColor;
        uniform vec4 uColor;

        void main(){
            FragColor = vec4(vColor, 1.0) * uColor;
        }
    )";
    //compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCstr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCstr, nullptr);
    glCompileShader(fragmentShader);

    //check if fragment shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    //if fragment shader compilation is unsuccessful, display the error
    if (!success) {
        
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    //combine vertex and fragment shaders into a single shader program
    //create obeject for shader program in the graphics card
    GLuint shaderProgram = glCreateProgram();
    //attach all shaders to this program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //link shaders together in the graphics pipeline
    glLinkProgram(shaderProgram);

    //check link status, check for errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    //if there is an error when linking, display the error
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;

    }

    //once the shader program has successfully linked we no longer need the individual shader objects
    // delete individual shader objects from gpu memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    

    //creating triangle structure
    std::vector<float> vertices =
    {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //vertex 1
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //vertex 2
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // vertex 3 
        0.5, -0.5, 0.0f, 1.0f, 1.0f, 0.0f //vertex 4
    };


    //defining square shape as two triangles with indices
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };
    //upload triangle vertex data to gpu memory using buffer
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //ebo tells open gl which vertices to draw and in what order
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //tell graphics pipeline/shader program how to interpret our data when it reaches the vertex shader
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, false , 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");
    

    while(!glfwWindowShouldClose(window)) {
        
        //change window background color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activate shader program
        glUseProgram(shaderProgram);

        //activate uniform which is a global gpu variable sent from the cpu to gpu we can use to tint the whole shape
        glUniform4f(uColorLoc, 1.0f, 0.0f, 0.0f, 0.0f);

        //bind vao containing our vertex layout
        glBindVertexArray(vao);
        //render triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //swapping the buffer so we can actually see the colored background
        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    //if we have exited the while loop above the window has been requested to be closed so now clean and clear the glfw library
    glfwTerminate();
    return 0;

}