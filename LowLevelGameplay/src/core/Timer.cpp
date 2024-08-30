#include "Timer.h"

#include "SceneManager.h"

namespace LLGP
{
    Timer::Timer(const float setTime, const bool oneShot): m_setTime(setTime), m_isOneShot(oneShot)
    {
        SceneManager::updateEvent.AddListener(this, std::bind(&Timer::Update, this, std::placeholders::_1));
        m_remainingTime = setTime;
    }

    Timer::~Timer()
    {
        SceneManager::updateEvent.RemoveListener(this, std::bind(&Timer::Update, this, std::placeholders::_1));
    }

    void Timer::Update(float deltaTime)
    {
        if (m_isTicking == false) return;

        m_remainingTime -= deltaTime;

        if (m_remainingTime > 0) return;

        m_remainingTime = 0;
        TimeOut.Emit();
        Reset();

        if (m_isOneShot)
        {
            Stop();
        }
        else
        {
            Start();
        }

    }
}
