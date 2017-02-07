#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <types.h>

class Actor;
class Entity;
typedef unsigned long EventType;

class Event
{
public:
    virtual ~Event() {}
	virtual EventType GetType() = 0;
	virtual std::string GetName() = 0;
};

enum EntityEventType
{
    ENTITY_CREATED = 0,
    ENTITY_DESTROYED
};

class EntityEvent : public Event
{
private:
    static const EventType sk_Type;
    Entity*                m_entity;
    EntityEventType        m_event_type;
    
public:
    EntityEvent(Entity* _entity) : m_entity(_entity) {}
    virtual ~EntityEvent() {}
    inline virtual EventType GetType()               { return sk_Type; }
    inline virtual std::string GetName()             { return "Entity Event"; }
    inline Entity* GetEntity()                       { return m_entity; }
    inline EntityEventType GetEntityEventType()      { return m_event_type; }
};


enum TriggerEventType
{
    TRIGGER_ENTERED = 0,
    TRIGGER_EXITED
};

class TriggerEvent : public Event
{
public:
    static const EventType sk_Type;
    
private:
    TriggerEventType       m_event_type;
    
public:
    TriggerEvent(TriggerEventType _type) : m_event_type(_type) {}
    virtual ~TriggerEvent() {}
    inline virtual EventType GetType()                         { return sk_Type; }
    inline virtual std::string GetName()                       { return "Entity Event"; }
    inline TriggerEventType GetTriggerEventType()              { return m_event_type; }
};


class InputActionEvent : public Event
{
public:
    static const EventType sk_Type;
    
private:
    uint64_t            m_action;
    
public:
    InputActionEvent(uint64_t _action) : m_action(_action) {}
    InputActionEvent(HashResult _action) : m_action(_action.hash) {}
    virtual ~InputActionEvent() {}
    inline virtual EventType GetType()                    { return sk_Type; }
    inline virtual std::string GetName()                  { return "Input Action Event"; }
    inline uint64_t GetAction()                         { return m_action; }
    inline HashResult get_action_hash()
    {
        HashResult result;
        result.hash = m_action;
        return result;
    }
};

class InputStateEvent : public Event
{
public:
    static const EventType sk_Type;
    
private:
    uint64_t            m_state;
    int                 m_value;
    
public:
    InputStateEvent(uint64_t _state, int _value) : m_state(_state), m_value(_value) {}
    InputStateEvent(HashResult _state, int _value) : m_state(_state.hash), m_value(_value) {}
    virtual ~InputStateEvent() {}
    inline virtual EventType GetType()                    { return sk_Type; }
    inline virtual std::string GetName()                  { return "Input State Event"; }
    inline uint64_t GetState()                        { return m_state; }
    inline int GetValue()                                 { return m_value; }
    inline HashResult get_state_hash()
    {
        HashResult result;
        result.hash = m_state;
        return result;
    }
};

class InputAxisEvent : public Event
{
public:
    static const EventType sk_Type;
    
private:
    uint64_t            m_axis;
    double                 m_value;
    double                 m_delta;
    
public:
    InputAxisEvent(uint64_t _axis, double _value, double _delta) : m_axis(_axis), m_value(_value), m_delta(_delta) {}
    InputAxisEvent(HashResult _axis, double _value, double _delta) : m_axis(_axis.hash), m_value(_value), m_delta(_delta) {}
    virtual ~InputAxisEvent() {}
    inline virtual EventType GetType()                    { return sk_Type; }
    inline virtual std::string GetName()                  { return "Input State Event"; }
    inline uint64_t GetAxis()                          { return m_axis; }
    inline double GetValue()                              { return m_value; }
    inline double GetDelta()                              { return m_delta; }
    inline HashResult get_axis_hash()
    {
        HashResult result;
        result.hash = m_axis;
        return result;
    }
};

enum FileWatcherEventType
{
    FILE_ADDED = 0,
    FILE_UPDATED
};

class FileWatcherEvent : public Event
{
private:
    static const EventType sk_Type;
    std::string            m_filename;
    FileWatcherEventType   m_event_type;
    
public:
    FileWatcherEvent(std::string _filename, FileWatcherEventType _type) : m_filename(_filename), m_event_type(_type) {}
    virtual ~FileWatcherEvent() {}
    inline virtual EventType GetType()                    { return sk_Type; }
    inline virtual std::string GetName()                  { return "Input State Event"; }
    inline std::string GetFilename()                      { return m_filename; }
    inline FileWatcherEventType GetEventType()            { return m_event_type; }
};

class LuaScriptUpdatedEvent : public Event
{
private:
    static const EventType sk_Type;
    std::string            _script;
    
public:
    LuaScriptUpdatedEvent(std::string script) : _script(script) {}
    virtual ~LuaScriptUpdatedEvent() {}
    inline virtual EventType GetType()                    { return sk_Type; }
    inline virtual std::string GetName()                  { return "Lua Script Updated Event"; }
    inline std::string get_script_name()                  { return _script; }
};

#endif
