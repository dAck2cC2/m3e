#ifndef __CPATH_SCANNER_H__
#define __CPATH_SCANNER_H__

#include "engine/IEngineScanner.h"
#include "media/MediaDefine.h"
#include "utils/ABase.h"

struct dirent;

_MEDIA_BEGIN

class CPathScanner : public IEngineScanner
{
public:
    explicit CPathScanner();
    virtual ~CPathScanner();

    virtual int processDirectory(
        const char *path, sp<IEngineScannerClient>& client);

    void setLocale(const char *locale);

    // extracts album art as a block of data
    //virtual char *extractAlbumArt(int fd) = 0;

protected:
    const char *locale() const;

private:
    // current locale (like "ja_JP"), created/destroyed with strdup()/free()
    char *mLocale;
    char *mSkipList;
    int *mSkipIndex;

    int doProcessDirectory(
        char *path, int pathRemaining, sp<IEngineScannerClient>& client, bool noMedia);
    int doProcessDirectoryEntry(
        char *path, int pathRemaining, sp<IEngineScannerClient>& client, bool noMedia,
        struct dirent* entry, char* fileSpot);
    void loadSkipList();
    bool shouldSkipDirectory(char *path);


    DISALLOW_EVIL_CONSTRUCTORS(CPathScanner);
};

_MEDIA_END

#endif // __CPATH_SCANNER_H__

