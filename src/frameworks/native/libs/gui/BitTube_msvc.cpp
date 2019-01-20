

#include <stdint.h>
//#include <sys/types.h>
//#include <sys/socket.h>

//#include <fcntl.h>
//#include <unistd.h>

#include <utils/Errors.h>

#include <binder/Parcel.h>

#include <gui/BitTube.h>

namespace android {
// ----------------------------------------------------------------------------

// Socket buffer size.  The default is typically about 128KB, which is much larger than
// we really need.  So we make it smaller.
static const size_t DEFAULT_SOCKET_BUFFER_SIZE = 4 * 1024;


BitTube::BitTube()
    : mSendFd(-1), mReceiveFd(-1)
{

}

BitTube::BitTube(size_t bufsize)
    : mSendFd(-1), mReceiveFd(-1)
{

}

BitTube::BitTube(const Parcel& data)
    : mSendFd(-1), mReceiveFd(-1)
{

}

BitTube::~BitTube()
{

}

void BitTube::init(size_t rcvbuf, size_t sndbuf) {

}

status_t BitTube::initCheck() const
{

    return NO_ERROR;
}

int BitTube::getFd() const
{
    return mReceiveFd;
}

int BitTube::getSendFd() const
{
    return mSendFd;
}

ssize_t BitTube::write(void const* vaddr, size_t size)
{
	return 0;
}

ssize_t BitTube::read(void* vaddr, size_t size)
{
    return 0;
}

status_t BitTube::writeToParcel(Parcel* reply) const
{
    if (mReceiveFd < 0)
        return -EINVAL;

    status_t result = reply->writeDupFileDescriptor(mReceiveFd);
    //close(mReceiveFd);
    mReceiveFd = -1;
    return result;
}


ssize_t BitTube::sendObjects(const sp<BitTube>& tube,
        void const* events, size_t count, size_t objSize)
{
    const char* vaddr = reinterpret_cast<const char*>(events);
    ssize_t size = tube->write(vaddr, count*objSize);

    // should never happen because of SOCK_SEQPACKET
    LOG_ALWAYS_FATAL_IF((size >= 0) && (size % static_cast<ssize_t>(objSize)),
            "BitTube::sendObjects(count=%zu, size=%zu), res=%zd (partial events were sent!)",
            count, objSize, size);

    //ALOGE_IF(size<0, "error %d sending %d events", size, count);
    return size < 0 ? size : size / static_cast<ssize_t>(objSize);
}

ssize_t BitTube::recvObjects(const sp<BitTube>& tube,
        void* events, size_t count, size_t objSize)
{
    char* vaddr = reinterpret_cast<char*>(events);
    ssize_t size = tube->read(vaddr, count*objSize);

    // should never happen because of SOCK_SEQPACKET
    LOG_ALWAYS_FATAL_IF((size >= 0) && (size % static_cast<ssize_t>(objSize)),
            "BitTube::recvObjects(count=%zu, size=%zu), res=%zd (partial events were received!)",
            count, objSize, size);

    //ALOGE_IF(size<0, "error %d receiving %d events", size, count);
    return size < 0 ? size : size / static_cast<ssize_t>(objSize);
}

// ----------------------------------------------------------------------------
}; // namespace android
