/*
 * Copyright (C) 2022, 2025 LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <fstream>
#include <map>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

static const std::string kGesturesPath =
    "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_gestures";

static const std::map<int32_t, GestureInfo> kGestureInfoMap = {
    {0, {0x2e8, "One finger up swipe", "up"}},
    {1, {0x2e9, "Letter e", "e"}},
    {2, {0x2ea, "Letter M", "m"}},
    {3, {0x2eb, "Letter W", "w"}},
    {4, {0x2ec, "Letter S", "s"}},
    {5, {0x2ed, "Letter V", "v"}},
    {6, {0x2ee, "Letter Z", "z"}},
    {7, {0x2ef, "Two fingers down swipe", "pause"}},
    {8, {0x2f0, "Left arrow", "rewind"}},
    {9, {0x2f1, "Right arrow", "forward"}},
};

ndk::ScopedAStatus TouchscreenGesture::getSupportedGestures(std::vector<Gesture>* _aidl_return) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }

    *_aidl_return = gestures;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    std::ofstream file(kGesturesPath);
    if (!file) {
        LOG(ERROR) << "Failed to open gestures file";
    }

    file << entry->second.type << "=" << enabled << std::endl;
    if (!file) {
        LOG(ERROR) << "Failed to write gesture " << entry->second.type << "=" << enabled;
        return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
