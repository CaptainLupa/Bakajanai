#pragma once

#ifndef POLYGONOBJECT_H
#define POLYGONOBJECT_H

#include "precomp.h"
#include "Text.h"

namespace Baka {

	class Polygon {
	protected:
		unsigned int VAO, VBO, EBO;

	public:
		Polygon() : VAO(0), VBO(0), EBO(0) {}

		virtual void setColorAttrib(unsigned int pos, int num, int stride, int offset) = 0;

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

#endif