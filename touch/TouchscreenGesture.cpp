/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"

#include <android-base/file.h>
#include <android-base/logging.h>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

using ::android::hardware::Void;

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
    {7, {0x2ef, "Two finger down swipe", "pause"}},
    {8, {0x2f0, "Left arrow", "rewind"}},
    {9, {0x2f1, "Right arrow", "forward"}},
};

Return<void> TouchscreenGesture::getSupportedGestures(getSupportedGestures_cb resultCb) {
    std::vector<Gesture> gestures;

    for (const auto& entry : kGestureInfoMap) {
        gestures.push_back({entry.first, entry.second.name, entry.second.keycode});
    }
    resultCb(gestures);

    return Void();
}

Return<bool> TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enabled) {
    const auto entry = kGestureInfoMap.find(gesture.id);
    if (entry == kGestureInfoMap.end()) {
        return false;
    }

    std::ofstream file(kGesturesPath);
    if (!file) {
        LOG(ERROR) << "Failed to open gestures file";
    }

    file << entry->second.type << "=" << enabled << std::endl;
    if (!file) {
        LOG(ERROR) << "Failed to write gesture " << entry->second.type << "=" << enabled;
        return false;
    }

    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
