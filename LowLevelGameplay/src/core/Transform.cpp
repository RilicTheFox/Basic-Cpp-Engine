#include "Transform.h"
#include <cmath>

#include "Math.h"

namespace LLGP
{
    Transform::Transform()
    {
        SetPosition(Vector2f(0, 0));
        SetRotation(0);
        SetScale(Vector2f(1, 1));
    }

    void Transform::SetRotation(float newRotation)
    {
        m_rotation = newRotation;

        float radians = (m_rotation + 90) * Math::DegToRad;
        m_up = Vector2f(-std::cos(radians), -std::sin(radians));
    }

    void Transform::SetUp(Vector2f newUp)
    {
        m_up = newUp.Normalised();

		float radians = std::atan2(m_up.x, -m_up.y);
        m_rotation = radians * Math::RadToDeg;
    }
}
