/*
NOU Framework - Created for INFR 2310 at Ontario Tech.
(c) Samantha Stahlke 2020

CPathAnimator.cpp
Simple component for animating an object along a path.

As a convention in NOU, we put "C" before a class name to signify
that we intend the class for use as a component with the ENTT framework.
*/

#include "CPathAnimator.h"
#include "NOU/App.h"
#include "NOU/Input.h"
#include "NOU/Entity.h"
#include "NOU/CCamera.h"
#include "NOU/CMeshRenderer.h"
#include "CPathAnimator.h"
#include "Tools/PathUtility.h"
#include "NOU/Shader.h"
#include "NOU/GLTFLoader.h"
#include <iostream>
#include "imgui.h"

#include <memory>
using namespace std;
template<typename T>
T LERP(const T& p0, const T& p1, float t)
{
	return (1.0f - t) * p0 + t * p1;
}

namespace nou
{
	CPathAnimator::CPathAnimator(Entity& owner)
	{
		m_owner = &owner;

		m_segmentIndex = 0;
		m_segmentTimer = 0.0f;

		m_segmentTravelTime = 1.0f;
		m_mode = PathSampler::PathMode::LERP;
	}

	void CPathAnimator::SetMode(PathSampler::PathMode mode)
	{
		m_mode = mode;
		m_segmentIndex = 0;
	}
	bool increaser = true;
	void CPathAnimator::Update(const PathSampler::KeypointSet& keypoints, float deltaTime)
	{
		auto p1 = glm::vec3(-1,-1,1);
		auto p2 = glm::vec3(3, -1, 1);
		std::cout << m_segmentTimer << std::endl;

		if (increaser == true)
		{
			m_segmentTimer += 0.001;
		}
		else if (increaser == false)
		{
			m_segmentTimer -= 0.001;
		}

		if (m_segmentTimer >= 1)
		{
			increaser = false;
		}
		else if (m_segmentTimer <= 0)
		{
			increaser = true;
		}
		else {
			m_owner->transform.m_pos = LERP(p1, p2, m_segmentTimer);
		}
		// TODO: Implement this function
		// Steps to follow:
		// Make sure we have points to use
		
	// Creating duck entity
		// Increment our t value
		// Handle switching segments each time t = 1

		// Work out t using segment timer and segment travel time


		// Ensure we have at least 2 points to LERP along
		// Need at least 2 points for 1 segment

		// Determine the indices of the points to LERP along (in our vector of key points)

		// Perform LERP using function in 
	}
}