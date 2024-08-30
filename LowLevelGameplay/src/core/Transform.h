#pragma once
#include <Vector2.h>

namespace LLGP
{
    class Transform
    {
    public:
        Transform();

        Vector2<float> GetPosition() { return m_position; }
        void SetPosition(Vector2f newPosition) { m_position = newPosition; }

        float GetRotation() { return m_rotation; }
        void SetRotation(float newRotation);

        Vector2f GetScale() { return m_scale; }
        void SetScale(Vector2f newScale) { m_scale = newScale; }

        Vector2f GetUp() { return m_up; }
        void SetUp(Vector2f newUp);

    private:
        Vector2f m_position;
        float m_rotation;
        Vector2f m_scale;

        Vector2f m_up;
    };
}
