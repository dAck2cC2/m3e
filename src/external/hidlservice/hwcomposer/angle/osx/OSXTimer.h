
#ifndef SF_NATIVE_OSX_TIMER_H_
#define SF_NATIVE_OSX_TIMER_H_

#include <stdint.h>
#include <time.h>

#include "com/Timer.h"

namespace android {

class OSXTimer : public Timer
{
  public:
    OSXTimer();

    void start() override;
    void stop() override;
    double getElapsedTime() const override;

  private:
    bool mRunning;
    uint64_t mStartTime;
    uint64_t mStopTime;
};

} /* namespace android */

#endif // SF_NATIVE_OSX_TIMER_H_
