
#include <stdint.h>
#include <sync/sync.h>

int sync_wait(int fd, int timeout)
{
    return -1;
}

int sync_merge(const char *name, int fd1, int fd2)
{
    return -1;
}

struct sync_fence_info_data *sync_fence_info(int fd)
{
    return 0;
}

struct sync_pt_info *sync_pt_info(struct sync_fence_info_data *info,
                                  struct sync_pt_info *itr)
{
    return 0;
}

void sync_fence_info_free(struct sync_fence_info_data *info)
{
}

