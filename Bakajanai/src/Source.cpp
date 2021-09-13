#include "Text.h"
#include "Shader.h"

// Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data : solution. DONE!
//
// Now create the same 2 triangles using two different VAOsand VBOs for their data : solution. DONE!
//
// Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; 
// draw both triangles again where one outputs the color yellow : solution.

bool wireFrameEnabled = false;
bool titleChanged = false;

unsigned int SCR_W = 800, SCR_H = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	glfwSetWindowSize(window, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		wireFrameEnabled = !wireFrameEnabled;
		glPolygonMode(GL_FRONT_AND_BACK, wireFrameEnabled ? GL_LINE : GL_FILL);
	} else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		titleChanged = !titleChanged;
		glfwSetWindowTitle(window, titleChanged ? "This shit poppin" : "Bakajanai");
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_W, SCR_H, "Bakajanai", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(16);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	float fart[ ] = {
		-0.5, -0.5, 0.0f,
		 0.5, -0.5, 0.0f,
		 0.0,  0.5, 0.0f
	};

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fart), fart, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Baka::Shader myShader("src/shaders/main.vert", "src/shaders/main.frag");

	float r, g, b;


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float t = glfwGetTime();
		b = sin(t);

		glBindVertexArray(VAO);

		myShader.use();

		myShader.setFloat4("ourColor", std::vector<float>({ 0.1f, 0.05f, b, 1.0f }));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}