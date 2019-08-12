#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
	}

	void cameraInitialise(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->positionVector = pos;
		this->forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
		this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionMat = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 getCameraPosition()
	{
		return this->positionVector;
	}

	inline glm::mat4 GetProjection() const
	{
		return projectionMat;
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(positionVector, positionVector + forwardVector, upVector);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projectionMat * glm::lookAt(positionVector, positionVector + forwardVector, upVector);
	}

	//void MoveForward(float amt)
	//{
	//	pos += forward * amt;
	//}

	//void MoveRight(float amt)
	//{
	//	pos += glm::cross(up, forward) * amt;
	//}

	//void Pitch(float angle)
	//{
	//	glm::vec3 right = glm::normalize(glm::cross(up, forward));

	//	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	//	up = glm::normalize(glm::cross(forward, right));
	//}

	//void RotateY(float angle)
	//{
	//	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	//	glm::mat4 rotation = glm::rotate(angle, UP);

	//	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	//	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	//}

protected:
private:
	glm::mat4 projectionMat;
	glm::vec3 positionVector;
	glm::vec3 forwardVector;
	glm::vec3 upVector;
};


