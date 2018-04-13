
#include <initrc.h>

#include <ui/DisplayInfo.h>

#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>

using namespace android;

static InitRC&   gInitrc = InitRC::getInstance();

class Animation : public Thread
{
public:
    Animation()
    :   Thread(false)
    {
        mSession = new SurfaceComposerClient();
    };
    
    ~Animation()
    {
        
    };
    
private:
    virtual bool        threadLoop()
    {
        return true;
    };
    
    virtual status_t    readyToRun()
    {
        sp<IBinder> dtoken(SurfaceComposerClient::getBuiltInDisplay(
                                                                    ISurfaceComposer::eDisplayIdMain));
        DisplayInfo dinfo;
        status_t status = SurfaceComposerClient::getDisplayInfo(dtoken, &dinfo);
        if (status)
            return -1;

        // create the native surface
        sp<SurfaceControl> control = session()->createSurface(String8("Animation"),
                                                              dinfo.w, dinfo.h, PIXEL_FORMAT_RGB_565);
        
        SurfaceComposerClient::openGlobalTransaction();
        control->setLayer(0x40000000);
        SurfaceComposerClient::closeGlobalTransaction();
        
        sp<Surface> s = control->getSurface();

        return NO_ERROR;
    };
    
    virtual void        onFirstRef()
    {
        run("BootAnimation", PRIORITY_DISPLAY);
    };

    sp<SurfaceComposerClient> session() const
    {
        return mSession;
    }
    
private:
    sp<SurfaceComposerClient> mSession;
};

int main(int argc, char** argv)
{
    sp<Animation> animation = new Animation();
    
    while (1) ;
    
    return 0;
}
