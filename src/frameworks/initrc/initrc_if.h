#ifndef _ANDROID_INIT_RC_IF_H
#define _ANDROID_INIT_RC_IF_H

#include <utils/RefBase.h>

namespace android {

class InitRCMainWindow : public virtual RefBase {
public:
	virtual void run() = 0;

protected:
	virtual ~InitRCMainWindow() {};
};

};

#endif // _ANDROID_INIT_RC_IF_H
