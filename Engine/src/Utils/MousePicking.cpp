#include "pch.h"
#include "MousePicking.h"
#include "Core/Input.h"

#include <glad/glad.h>

namespace Utils {

	void ReadColorAttachment()
	{
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		auto [xpos, ypos] = Input::GetMousePos();
		glReadPixels(xpos, 720.0f - ypos - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(xpos, 720.0f - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(xpos, 720.0f - ypos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel (%d, %d), color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
			xpos, 720 - ypos - 1, color[0], color[1], color[2], color[3], depth, index);
	}

	int GetStencilIndex()
	{
		GLuint index;

		auto [xpos, ypos] = Input::GetMousePos();
		glReadPixels(xpos, 720.0f - ypos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		return index;
	}
}