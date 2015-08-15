
#define LOG_TAG  "CMediaFileScanner"
#include "media/CMediaFileScanner.h"
#include "media/CFileSource.h"
#include "media/MediaExtractor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

_MEDIA_BEGIN

CMediaFileScanner::CMediaFileScanner()
{
}

CMediaFileScanner::~CMediaFileScanner()
{
}

int
CMediaFileScanner::processFile(
    const char *path, const char *mimeType, const sp<IEngineScannerClient>& client
)
{
    if (client == NULL) {
        return BAD_VALUE;
    }

    const char *extension = strrchr(path, '.');

    if (!extension) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    if (!FileHasAcceptableExtension(extension)) {
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    if (!strcasecmp(extension, ".mid")
            || !strcasecmp(extension, ".smf")
            || !strcasecmp(extension, ".imy")
            || !strcasecmp(extension, ".midi")
            || !strcasecmp(extension, ".xmf")
            || !strcasecmp(extension, ".rtttl")
            || !strcasecmp(extension, ".rtx")
            || !strcasecmp(extension, ".ota")
            || !strcasecmp(extension, ".mxmf")) {
        //return HandleMIDI(path, &client);
        return MEDIA_SCAN_RESULT_SKIPPED;
    }

    sp<IDataSource> pSrc = new CFileSource(path);
    status_t err;

    if ((err = pSrc->initCheck())) {
        pSrc.clear();
        return (err);
    }

    sp<MediaExtractor> pExtractor = MediaExtractor::Create(pSrc);

    if (pExtractor == NULL) {
        pSrc.clear();
        return (MEDIA_SCAN_RESULT_SKIPPED);
    }

    // get it back to client
    client->foundMediaFile(path, pExtractor);

    return (MEDIA_SCAN_RESULT_OK);
}

bool
CMediaFileScanner::FileHasAcceptableExtension(const char *extension)
{
    static const char *kValidExtensions[] = {
        ".mp3", ".mp4", ".m4a", ".3gp", ".3gpp", ".3g2", ".3gpp2",
        ".mpeg", ".ogg", ".mid", ".smf", ".imy", ".wma", ".aac",
        ".wav", ".amr", ".midi", ".xmf", ".rtttl", ".rtx", ".ota",
        ".mkv", ".mka", ".webm", ".ts", ".fl", ".flac", ".mxmf",
        ".avi", ".mpeg", ".mpg"
    };
    static const size_t kNumValidExtensions =
        sizeof(kValidExtensions) / sizeof(kValidExtensions[0]);

    for (size_t i = 0; i < kNumValidExtensions; ++i) {
        if (!strcasecmp(extension, kValidExtensions[i])) {
            return true;
        }
    }

    return false;
}


_MEDIA_END

