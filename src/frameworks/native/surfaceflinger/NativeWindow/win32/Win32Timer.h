
#ifndef SF_NATIVE_WIN32_TIMER_H
#define SF_NATIVE_WIN32_TIMER_H

#include <windows.h>

#include "NativeWindow/Timer.h"

namespace android {

class WindowsTimer : public Timer
{
  public:
    WindowsTimer();

    void start() override;
    void stop() override;
    double getElapsedTime() const override;

  private:
    bool mRunning;
    LONGLONG mStartTime;
    LONGLONG mStopTime;

    LONGLONG mFrequency;
};

} /* namespace android */

#endif  // SF_NATIVE_WIN32_TIMER_H
