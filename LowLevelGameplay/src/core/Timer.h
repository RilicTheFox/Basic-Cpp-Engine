#pragma once
#include "Signal.h"

namespace LLGP
{
    class Timer
    {
    public:
        explicit Timer(float setTime, bool oneShot);
        ~Timer();

        void Start() { m_isTicking = true; }
        void Stop() { m_isTicking = false; }
        void Reset() { m_remainingTime = m_setTime; }
        float GetTimeRemaining() { return m_remainingTime; }
        bool IsRunning() { return m_isTicking; }

        Signal<> TimeOut;

    private:
        void Update(float deltaTime);

        bool m_isTicking = false;
        float m_setTime = 3.f;
        bool m_isOneShot = false;
        float m_remainingTime = 0.f;

    };
}
