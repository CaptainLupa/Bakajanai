#include "Text.h"
#include "Shader.h"
#include "PolygonObject.h"

bool wireFrameEnabled = false;
bool titleChanged = false;

unsigned int SCR_W = 800, SCR_H = 600;
float swagVariable = 0.0f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	glfwSetWindowSize(window, width, height);
}

template<typename T>
unsigned int sizeOfVec(const std::vector<T>& vec) {
	return sizeof(T) * vec.size();
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

	//glfwSwapInterval(16);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}


	stbi_set_flip_vertically_on_load(true);

	
	unsigned int texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// stp == xyz6
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	unsigned char* data = stbi_load("images/veggie.png", &width, &height, &channels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << Baka::BakaText("Failed to load Texture\n", Baka::BakaColors::RED);
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("images/Cutie.png", &width, &height, &channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << Baka::BakaText("Failed to load Texture\n", Baka::BakaColors::RED);
	}
	stbi_image_free(data);

	std::vector<float> vertices({
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	});

	std::vector<unsigned int> indices({ 0, 1, 3, 1, 2, 3 });


	/*unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVec(vertices), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfVec(indices), indices.data(), GL_STATIC_DRAW);*/

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//// texture coord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	

	Baka::Square sq(vertices, indices, 8);
	sq.setColorAttrib(1, 3, 8, 3);
	sq.setTexAttrib(2, 2, 8, 6);

	Baka::Shader myShader("src/shaders/main.vert", "src/shaders/main.frag");

	myShader.use();

	//myShader.setInt("ourTexture", 0);
	//myShader.setInt("texture2", 1);

	float r, g, b;
	float x = 0.0f, y = 0.0f;
	float xVel = 0.016f, yVel = -0.018f;


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float t = glfwGetTime();
		myShader.setFloat("time", t);
		x += xVel;
		y += yVel;

		r = abs(x);
		g = abs(y);
		b = abs(x);

		std::cout << Baka::BakaText("x: ", Baka::BakaColors::YELLOW) << Baka::BakaText(x, Baka::BakaColors::YELLOW) << std::endl;
		std::cout << Baka::BakaText("y: ", Baka::BakaColors::YELLOW) << Baka::BakaText(y, Baka::BakaColors::YELLOW) << std::endl;

		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		if (x > 0.5 or x < -0.5)
			xVel = -xVel;

		if (y > 0.5 or y < -0.5)
			yVel = -yVel;

		myShader.use();

		myShader.setFloat("coom", swagVariable);

		myShader.setFloat("hOffset", x);
		myShader.setFloat("vOffset", y);

		//myShader.setFloat4("c", std::vector<float>({ r, g, b, 1.0f}));

		sq.enable();
		sq.draw();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}