#ifndef RESTONCE_OBSERVER_H
#define RESTONCE_OBSERVER_H

namespace restonce {

class Subject;
// 观察者类，仅供子类和观察主题使用
class Observer
{
    friend class Subject; // 审明抽象Subject为友元类
protected:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void onSubjectChanged() = 0;
};

} // namespace restonce

#endif // RESTONCE_OBSERVER_H
