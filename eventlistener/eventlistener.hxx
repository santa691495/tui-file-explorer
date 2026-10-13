#include <functional>
#include <unordered_map>

#ifndef EVENT_LISTENER_HXX
#define EVENT_LISTENER_HXX

class EventListener
{
    private:
        std::unordered_map<int, std::function<void()>> keyToEventMapping;

    public:
        void mapKeyToEvent(int inputKey, std::function<void()> event);
        void registerForInput(int inputKey) const;
};

#endif
