#include "Component.h"
#include "SceneManager.h"

namespace LLGP
{
    Component::Component(GameObject* owner) : _gameObject(owner)
    {
        _gameObject->OnCollisionEnter.AddListener(this, std::bind(&Component::OnCollisionEnter, this, std::placeholders::_1));
        _gameObject->OnCollisionStay.AddListener(this, std::bind(&Component::OnCollisionStay, this, std::placeholders::_1));
        _gameObject->OnCollisionExit.AddListener(this, std::bind(&Component::OnCollisionExit, this, std::placeholders::_1));
    }
}
