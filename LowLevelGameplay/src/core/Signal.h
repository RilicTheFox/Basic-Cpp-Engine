#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

// This is not the one from Blackboard, I tried investigating my own event system.
// I did this as people were having a few issues with Events earlier in the module 
// and I was wondering about how they worked in the first place.
// So I decided to try to make my own!
namespace LLGP
{
    // The Listener is a container structure that lets the std::function pointers be compared against each other.
    // On their own, they can't actually be compared with == or !=. Which is silly, in my opinion.
    template<typename... T>
    class Listener
    {
    public:
        std::function<void(T...)> functionPointer;
        void* objectPointer;

        Listener(void* objectPointer, std::function<void(T...)> functionPointer)
        {
            this->objectPointer = objectPointer;
            this->functionPointer = functionPointer;
        }

        // Add comparison operators, using the object pointer as the comparator.
        bool operator== (Listener rhs)
        {
            return this->objectPointer == rhs.objectPointer;
        }
#if !_HAS_CXX20
        bool operator!= (Listener rhs)
        {
            return this->objectPointer != rhs.objectPointer;
        }
#endif
    };

    // The Signal class, the class that actually stores the Listeners.
    template<typename... T>
    class Signal
    {
    public:
        Signal()
        {
            m_listeners = std::vector<Listener<T...>>();
        }

        void AddListener(void* object, std::function<void(T...)> function)
        {
            // Package into a Listener structure.
            Listener listener = Listener(object, function);

            // Check if it is in the listeners vector.
            if (std::find(m_listeners.begin(), m_listeners.end(), listener) != m_listeners.end())
                return;

            // Add it.
            m_listeners.push_back(listener);
        }

        void RemoveListener(void* object, std::function<void(T...)> function)
        {
            // Package into a Listener structure.
            Listener listener = Listener(object, function);

            // Try to find the listener specified.
            auto iterator = std::find(m_listeners.begin(), m_listeners.end(), listener);

            // If it can't find it, return.
            if (iterator == m_listeners.end()) return;

            // Delete it.
            m_listeners.erase(iterator);
        }

        void Emit(T... args)
        {
            // For every function pointer inside the vector...
            // (side note: this won't work as a for-each loop :/ )
            for (int i = 0; i < m_listeners.size(); i++)
            {
                // Call with the template arguments.
                m_listeners[i].functionPointer(static_cast<T&&>(args)...);
            }
        }

    private:
        // Vector of Listener structs containingfunction pointers with the specific argument types we want.
        std::vector<Listener<T...>> m_listeners;
    };

}
