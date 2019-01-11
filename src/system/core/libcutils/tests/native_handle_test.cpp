
#include <gtest/gtest.h>
#include <cutils/native_handle.h>

//#include <stdlib.h>
#include <fcntl.h>

#define TEST_FDS  (3)
#define TEST_INTS (6)

static const char * TEST_FILE[TEST_FDS] = {
    "test_file_0",
    "test_file_1",
    "test_file_2"
};

#if 0
TEST(libcutils, native_handle_init)
{
    void* storage = malloc(sizeof(native_handle_t) + sizeof(int) * (TEST_FDS + TEST_INTS));
    EXPECT_TRUE(storage != NULL);
    
    native_handle_t* handle = native_handle_init((char*)storage, TEST_FDS, TEST_INTS);
    EXPECT_EQ(storage, handle);
    EXPECT_EQ(TEST_FDS, handle->numFds);
    EXPECT_EQ(TEST_INTS, handle->numInts);
    
    native_handle_delete(handle);
}
#endif 

TEST(libcutils, native_handle_create)
{
    native_handle_t* handle = native_handle_create(TEST_FDS, TEST_INTS);
    EXPECT_TRUE(handle != NULL);
    EXPECT_EQ(TEST_FDS, handle->numFds);
    EXPECT_EQ(TEST_INTS, handle->numInts);
    
    native_handle_delete(handle);
}

TEST(libcutils, native_handle_close)
{
    native_handle_t* handle = native_handle_create(TEST_FDS, TEST_INTS);
    EXPECT_TRUE(handle != NULL);
    EXPECT_EQ(TEST_FDS, handle->numFds);
    EXPECT_EQ(TEST_INTS, handle->numInts);
    
    for (int i = 0; i < TEST_FDS; ++i) {
        handle->data[i] = open(TEST_FILE[i], O_CREAT, 0);
        EXPECT_GE(handle->data[i], 0) << handle->data[i];
    }

    native_handle_close(handle);
    native_handle_delete(handle);
    
    for (int i = 0; i < TEST_FDS; ++i) {
        remove(TEST_FILE[i]);
    }
}

#if 0
TEST(libcutils, native_handle_clone)
{
    native_handle_t* handle = native_handle_create(TEST_FDS, TEST_INTS);
    EXPECT_TRUE(handle != NULL);
    EXPECT_EQ(TEST_FDS, handle->numFds);
    EXPECT_EQ(TEST_INTS, handle->numInts);
    
    for (int i = 0; i < TEST_FDS; ++i) {
        handle->data[i] = open(TEST_FILE[i], O_CREAT, 0);
        EXPECT_GE(handle->data[i], 0) << handle->data[i];
    }
    
    for (int i = 0; i < TEST_INTS; ++i) {
        handle->data[TEST_FDS + i] = i;
    }
    
    native_handle_t* clone = native_handle_clone(handle);
    EXPECT_TRUE(clone != NULL);
    EXPECT_NE(handle, clone);
    EXPECT_EQ(handle->numFds, clone->numFds);
    EXPECT_EQ(handle->numInts, clone->numInts);

    for (int i = 0; i < TEST_INTS; ++i) {
        EXPECT_EQ(handle->data[TEST_FDS + i], clone->data[TEST_FDS + i]) << i;
    }
    
    native_handle_close(handle);
    native_handle_delete(handle);
    native_handle_close(clone);
    native_handle_delete(clone);
    
    for (int i = 0; i < TEST_FDS; ++i) {
        remove(TEST_FILE[i]);
    }
}
#endif
