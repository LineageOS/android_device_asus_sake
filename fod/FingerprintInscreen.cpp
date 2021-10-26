/*
 * Copyright (C) 2021 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "FingerprintInscreenService"

#include <android-base/file.h>
#include "FingerprintInscreen.h"

#include <hidl/HidlTransportSupport.h>

#define GLOBAL_HBM_PATH "/proc/globalHbm"
#define GLOBAL_HBM_ON "1"
#define GLOBAL_HBM_OFF "0"

#define FOD_TOUCHED_PATH "/sys/class/drm/fod_touched"
#define FOD_TOUCHED_ON "1"
#define FOD_TOUCHED_OFF "0"

#define FP_MODE_PATH "/sys/devices/platform/soc/990000.i2c/i2c-1/1-0038/fts_fp_mode"
#define FP_MODE_NOTIFY_ON "1"
#define FP_MODE_NOTIFY_OFF "0"

namespace vendor {
namespace lineage {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_0 {
namespace implementation {

FingerprintInscreen::FingerprintInscreen() {
    this->mGoodixFingerprintDaemon = IGoodixFingerprintDaemon::getService();
}

Return<void> FingerprintInscreen::onStartEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    this->mGoodixFingerprintDaemon->sendCommand(200001, {},
                                                [](int, const hidl_vec<signed char>&) {});
    if (!android::base::WriteStringToFile(FOD_TOUCHED_ON, FOD_TOUCHED_PATH)) {
        ALOGE("Failed to write to %s", FOD_TOUCHED_PATH);
    }
    if (!android::base::WriteStringToFile(GLOBAL_HBM_ON, GLOBAL_HBM_PATH)) {
        ALOGE("Failed to write to %s", GLOBAL_HBM_PATH);
    }
    this->mGoodixFingerprintDaemon->sendCommand(200002, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    if (!android::base::WriteStringToFile(GLOBAL_HBM_OFF, GLOBAL_HBM_PATH)) {
        ALOGE("Failed to write to %s", GLOBAL_HBM_PATH);
    }
    this->mGoodixFingerprintDaemon->sendCommand(200003, {},
                                                [](int, const hidl_vec<signed char>&) {});
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    if (!android::base::WriteStringToFile(FP_MODE_NOTIFY_ON, FP_MODE_PATH)) {
        ALOGE("Failed to write to %s", FP_MODE_PATH);
    }
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    android::base::WriteStringToFile(FP_MODE_NOTIFY_OFF, FP_MODE_PATH);
    android::base::WriteStringToFile(GLOBAL_HBM_OFF, GLOBAL_HBM_PATH);
    android::base::WriteStringToFile(FOD_TOUCHED_OFF, FOD_TOUCHED_PATH);
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t, int32_t) {
    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t, int32_t) {
    return false;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t) {
    return 0;
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
    return false;
}

Return<void> FingerprintInscreen::setCallback(const sp<IFingerprintInscreenCallback>&) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getPositionX() {
    return 435;
}

Return<int32_t> FingerprintInscreen::getPositionY() {
    return 1631;
}

Return<int32_t> FingerprintInscreen::getSize() {
    return 220;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace lineage
}  // namespace vendor
