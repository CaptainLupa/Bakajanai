#include "precomp.h"
#include "PolygonObject.h"
#include "Shader.h"
#include "Text.h"
#include "GlfwUtilFunctions.h"

bool wireFrameEnabled = false;
bool titleChanged = false;

unsigned int SCR_W = 800, SCR_H = 600;
float swagVariable = 0.0f;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		wireFrameEnabled = !wireFrameEnabled;
		glPolygonMode(GL_FRONT_AND_BACK, wireFrameEnabled ? GL_LINE : GL_FILL);
	} else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		titleChanged = !titleChanged;
		glfwSetWindowTitle(window, titleChanged ? "This shit poppin" : "Bakajanai");
	} else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		swagVariable += 0.01f;
		if (swagVariable > 1.0f)
			swagVariable = 1.0f;
	} else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		swagVariable -= 0.01f;
		if (swagVariable < 0.0f)
			swagVariable = 0.0f;
	}
}

int main(void) {
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

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	std::vector<float> vertices({
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	});

	std::vector<unsigned int> indices({ 0, 1, 3, 1, 2, 3 });

	Baka::Square sq(vertices, indices, 8);
	sq.setColorAttrib(1, 3, 8, 3);
	sq.setTexAttrib(2, 2, 8, 6);

	Baka::Shader myShader("src/shaders/main.vert", "src/shaders/main.frag");

	myShader.createTexture("veggie.png");
	myShader.createTexture("Cutie.png");

	myShader.use();
	myShader.setInt("ourTexture", 0);
	myShader.setInt("texture2", 1);
	myShader.suspend();

	float x = 0.0f, y = 0.0f;
	float xVel = 0.016f, yVel = -0.018f;


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float t = glfwGetTime();
		
		x += xVel;
		y += yVel;

		myShader.use();
		myShader.useTexture(0);
		myShader.setActiveTextureUnit(1);
		myShader.useTexture(1);

		if (x > 0.5 || x < -0.5)
			xVel = -xVel;

		if (y > 0.5 or y < -0.5)
			yVel = -yVel;

		myShader.setFloat("time", t);

		myShader.setFloat("coom", swagVariable);

		myShader.setFloat("hOffset", x);
		myShader.setFloat("vOffset", y);

		sq.enable();
		sq.draw();
		sq.disable();

		myShader.suspend();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}