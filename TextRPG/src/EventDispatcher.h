#pragma once
#include <map>
#include <vector>
#include <functional>
using namespace std;

class EventDispatcher
{
public:
    EventDispatcher();
    virtual ~EventDispatcher();

    typedef function<void(void)> EventListener;

    void AddEventListener(const string& eventName, EventListener listener);
    void RemoveEventListener(const string& eventName, EventListener listener);

protected:
    void TriggerEvent(const string& eventName);

    map<string, vector<EventListener> > EventListeners;
};