#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream> //03
#include <string> //03

GLFWwindow* window;

bool initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to Initialize GLFW" << std::endl;
		return false;
	}

	//Create a new GLFW window
	window = glfwCreateWindow(800, 800, "INFR1350U", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	return true;
}

bool initGLAD() {
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		std::cout << "Failed to initialize Glad" << std::endl;
		return false;
	}
}





GLuint shader_program;

bool loadShaders() {
	// Read Shaders from file
	std::string vert_shader_str;
	std::ifstream vs_stream("vertex_shader.glsl", std::ios::in);
	if (vs_stream.is_open()) {
		std::string Line = "";
		while (getline(vs_stream, Line))
			vert_shader_str += "\n" + Line;
		vs_stream.close();
	}
	else {
		printf("Could not open vertex shader!!\n");
		return false;
	}
	const char* vs_str = vert_shader_str.c_str();

	std::string frag_shader_str;
	std::ifstream fs_stream("frag_shader.glsl", std::ios::in);
	if (fs_stream.is_open()) {
		std::string Line = "";
		while (getline(fs_stream, Line))
			frag_shader_str += "\n" + Line;
		fs_stream.close();
	}
	else {
		printf("Could not open fragment shader!!\n");
		return false;
	}
	const char* fs_str = frag_shader_str.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_str, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_str, NULL);
	glCompileShader(fs);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, fs);
	glAttachShader(shader_program, vs);
	glLinkProgram(shader_program);

	return true;
}


int main() {
	//Initialize GLFW
	if (!initGLFW())
		return 1;

	//Initialize GLAD
	if (!initGLAD())
		return 1;

	////////// LECTURE 3 //////////////

	static const GLfloat points[] = {
		//X, Y, Z
		-1.f, -0.5f, 0.5f, //vert1
		0.f, -0.5f, 0.5f, //vert2
		-0.5f, 0.5f, 0.5f, //vert3
		0.f, -0.5f, 0.5f, //vert4
		1.f, -0.5f, 0.5f, //vert5
		0.5f, 0.5f, 0.5f //vert6 (top vertex)
	};

	//static const GLfloat points2[] = {
	//	//X, Y, Z
	//	0.5f, -0.5f, 0.5f, //vert1
	//	1.5f, -0.5f, 0.5f, //vert2
	//	1.0f, 0.5f, 0.5f //vert3 (top vertex)
	//};

	static const GLfloat colors[] = {
		//R, G, B
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.8f, 0.0f, 0.0f,
		0.0f, 0.1f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	// Vertex Buffer Object - VBO
	GLuint pos_vbo = 0;
	glGenBuffers(1, &pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	// index, size, type, normalized?, stride, pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint color_vbo = 1;
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	////new VBO
	//GLuint pos_vbo2 = 2;
	//glGenBuffers(1, &pos_vbo2);
	//glBindBuffer(GL_ARRAY_BUFFER, pos_vbo2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW); //sets where the vertices are (look at points function)
	//// index, size, type, normalized?, stride, pointer
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	////VBO end

	////new vbo color because need it at a new position maybe?
	//GLuint color_vbo2 = 3;
	//glGenBuffers(1, &color_vbo2);
	//glBindBuffer(GL_ARRAY_BUFFER, color_vbo2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Enable the VBOs
	glEnableVertexAttribArray(0);//pos
	glEnableVertexAttribArray(1);//colors
	//glEnableVertexAttribArray(2);//triangle 2
	//glEnableVertexAttribArray(3);//colors for triangle 2

	if (!loadShaders())
		return 1;

	// GL STATES
	glEnable(GL_DEPTH_TEST);


	///// Game loop /////
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_program);
		// triangles, initial vertex, how many vertices?
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawArrays(GL_TRIANGLES, 2, 3);
		
		glfwSwapBuffers(window);
	}
	return 0;

}