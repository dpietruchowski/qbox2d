#ifndef QB2OBJECT_H
#define QB2OBJECT_H

class QEvent;
class QB2ContactEvent;

class QB2Object
{
public:
    QB2Object() = default;

public:
    virtual void OnUpdate();

protected:
    bool OnEvent(QEvent* event);
    virtual void OnBeginContact(QB2ContactEvent* contactEvent);
    virtual void OnEndContact(QB2ContactEvent* contactEvent);
    virtual void OnPreSolveContact(QB2ContactEvent* contactEvent);
    virtual void OnPostSolveContact(QB2ContactEvent* contactEvent);
};

#endif // QB2OBJECT_H
