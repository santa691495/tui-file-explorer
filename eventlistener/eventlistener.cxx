#include <functional>
#include <unordered_map>
#include "eventlistener.hxx"

void EventListener::mapKeyToEvent(int inputKey, std::function<void()> event)
{
    keyToEventMapping.insert({inputKey, event});
}

void EventListener::registerForInput(int inputKey) const
{
    auto it = keyToEventMapping.find(inputKey);
    if(it != keyToEventMapping.end())
    {
        keyToEventMapping.at(inputKey)();
    }
}
