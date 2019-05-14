
#ifndef SF_NATIVE_TIMER_H
#define SF_NATIVE_TIMER_H

namespace android {

class Timer
{
  public:
    virtual ~Timer() {}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual double getElapsedTime() const = 0;
};

Timer *CreateTimer();

} /* namespace android */

#endif // SF_NATIVE_TIMER_H
