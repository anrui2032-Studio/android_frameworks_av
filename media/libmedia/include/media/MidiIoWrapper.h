/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIDI_IO_WRAPPER_H_
#define MIDI_IO_WRAPPER_H_

#include <libsonivox/eas_types.h>
#include <utils/Mutex.h>

namespace android {

struct CDataSource;

class MidiIoWrapper {
public:
    explicit MidiIoWrapper(const char *path);
    explicit MidiIoWrapper(int fd, off64_t offset, int64_t size);
    explicit MidiIoWrapper(CDataSource *csource);

    ~MidiIoWrapper();

    int readAt(void *buffer, int offset, int size);
    int unbufferedReadAt(void *buffer, int offset, int size);
    int size();

    EAS_FILE_LOCATOR getLocator();

private:
    enum {
        kTotalCacheSize      = 1024 * 1024 + 512 * 1024,
        kSingleCacheSize     = 65536,
    };

    int mFd;
    off64_t mBase;
    int64_t  mLength;
    class DataSourceUnwrapper;
    DataSourceUnwrapper *mDataSource;
    EAS_FILE mEasFile;
    unsigned char *mCacheBuffer;
    int64_t mCacheBufRangeLength;
    static int sCacheBufferSize;
    static Mutex mCacheLock;
};


}  // namespace android

#endif // MIDI_IO_WRAPPER_H_
