#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(uint32_t width, uint32_t height, const glm::vec3& position)
	: m_AspectRatio((float)width/(float)height), m_Projection(glm::ortho(-m_AspectRatio * 5.0f, m_AspectRatio * 5.0f, -5.0f, 5.0f, -1.0f, 1.0f)), m_Position(position)
{
	RecalculateViewProjection();
}

Camera::~Camera()
{
}

void Camera::OnUpdate()
{
	if (m_TransitionTime == -1.0f)
	{
		m_Angle += 180.0f;
		m_Time = 0.0f;
		m_TransitionTime = 0.0f;
	}
	if (m_Time > 0.0f)
	{
		double ts = 1.0f / 60.0f;
		m_Time -= ts;
		m_Angle += 180.0f * ts / m_TransitionTime;
		//if (m_Time <= 0.0f)
		//	m_Angle += 180.0f;
	}
	RecalculateViewProjection();
}

void Camera::TurnChange(double time)
{
	m_TransitionTime = time;
	m_Time = time;
}

void Camera::RecalculateViewProjection()
{
	glm::mat4 view = glm::translate(glm::mat4(1.0f), m_Position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_Angle), glm::vec3(0, 0, 1));
	m_ViewProjection = m_Projection * glm::inverse(view);
}
