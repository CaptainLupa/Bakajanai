#pragma once

#ifndef GLFWUTILFUNCTIONS_H
#define GLFWUTILFUNCTIONS_H

#include "precomp.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	glfwSetWindowSize(window, width, height);
}


#endif