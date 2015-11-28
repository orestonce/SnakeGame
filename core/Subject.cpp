#include "Subject.h"
#include "Observer.h"

namespace restonce {

void Subject::attachObserver (Observer *o)
{
    m_observers.insert (o);
}

void Subject::notifyObservers ()
{
    for(Observer *o : m_observers )
    {
        o->onSubjectChanged ();
    }
}

} // namespace restonce
