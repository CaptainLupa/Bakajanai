#pragma once

#include "precomp.h"

namespace Baka {
	// TODO: Add Texture class of some sort

	class Polygon {
	protected:
		unsigned int VAO, VBO, EBO;

	public:
		virtual void draw() = 0;

		virtual void enable() = 0;
		virtual void disable() = 0;
	};
	
	class Triangle: Polygon {
	public:
		//unsigned int VAO, VBO;

		Triangle(std::vector<float> verts, int stride);

		void setColorAttrib(unsigned int pos, int num, int stride, int offset);
		void setTexAttrib(unsigned int pos, int num, int stride, int offset);

		void draw();

		void enable();
		void disable();
	};

	class Square: Polygon {
	public:
		// unsigned int VAO, VBO, EBO;

		Square(std::vector<float> verts, std::vector<unsigned int> indices, int stride);

		void setColorAttrib(unsigned int pos, int num, int stride, int offset);
		void setTexAttrib(unsigned int pos, int num, int stride, int offset);

		void draw();

		void enable();
		void disable();
	};

	template<typename T>
	unsigned int sizeOfVec(const std::vector<T>& vec) {
		return sizeof(T) * vec.size();
	}
}