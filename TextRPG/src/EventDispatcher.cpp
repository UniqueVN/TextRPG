#include <map>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
#include "UIComponent.h"
#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::AddEventListener(const string& eventName, EventListener listener)
{
    if (listener == nullptr)
        return;

    auto eventIt = EventListeners.find(eventName);
    // Add new array for the listeners of the event if no one listen to it yet
    if (eventIt == EventListeners.end())
    {
        EventListeners.insert(pair<string, vector<EventListener> >(eventName, vector<EventListener>()));
        eventIt = EventListeners.find(eventName);
    }

    // Add the new listener to the list of all listeners
    (eventIt->second).push_back(listener);
}

void EventDispatcher::RemoveEventListener(const string& eventName, EventListener listener)
{
    auto eventIt = EventListeners.find(eventName);

    if (eventIt == EventListeners.end())
        return;

    auto& listeners = (eventIt->second);
    // Find the listener in the list
    // FIXME: Right now we compare 2 std::function by their target which may not be correct.
    auto listenerIt = find_if(listeners.begin(), listeners.end(), 
        [&listener](EventListener aListener)->bool { return aListener.target<void(void)>() == listener.target<void(void)>(); });
    // Remove the listener from the list if found
    if (listenerIt != listeners.end())
        listeners.erase(listenerIt);
}

void EventDispatcher::TriggerEvent(const string& eventName)
{
    auto eventIt = EventListeners.find(eventName);
    if (eventIt == EventListeners.end())
        return;

    // Call all the listeners which is listening to this event
    auto eventListeners = eventIt->second;
    for (auto& listener : eventListeners)
    {
        if (listener != nullptr)
            listener();
    }
}
