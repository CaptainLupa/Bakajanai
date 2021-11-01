#include "PolygonObject.h"

namespace Baka {
	Triangle::Triangle(std::vector<float> verts, int stride = 8) {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVec(verts), verts.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Triangle::enable() {
		glBindVertexArray(VAO);
	}

	void Triangle::disable() {
		glBindVertexArray(0);
	}

	void Triangle::draw() {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Triangle::setColorAttrib(unsigned int pos = 1, int num = 3, int stride = 8, int offset = 3) {
		glBindVertexArray(VAO); // Bind objects buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(pos, num, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float))); // Set values
		glEnableVertexAttribArray(pos);
		glBindVertexArray(0); // Unbind Buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Triangle::setTexAttrib(unsigned int pos = 2, int num = 2, int stride = 8, int offset = 6) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(pos, num, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(pos);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	
	/// <summary>
	/// Creates a Square object with color and texture.  Uses EBO so only 4 vertices required.
	/// </summary>
	/// <param name="verts">Raw vertices data</param>
	/// <param name="indices">What order to read and reread verts to make a square</param>
	/// <param name="stride">"Length" of each vertex, 3 for only position, 6 for pos and color, and 8 for texture.</param>
	Square::Square(std::vector<float> verts, std::vector<unsigned int> indices, int stride = 8) {
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVec(verts), verts.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfVec(indices), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // DO NOT UNBIND WHEN DRAWING!!!!!!
		glBindVertexArray(0);
	}
	
	void Square::enable() {
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void Square::disable() {
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	

	// only works if object is enabled
	void Square::draw() {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Square::setColorAttrib(unsigned int pos = 1, int num = 3, int stride = 8, int offset = 3) {
		glBindVertexArray(VAO); // Bind objects buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(pos, num, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float))); // Set values
		glEnableVertexAttribArray(pos);
		glBindVertexArray(0); // Unbind Buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Square::setTexAttrib(unsigned int pos = 2, int num = 2, int stride = 8, int offset = 6) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(pos, num, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(pos);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}