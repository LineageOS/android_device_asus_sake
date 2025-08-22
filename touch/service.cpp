/*
 * Copyright (C) 2021, 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.sake"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "GloveMode.h"
#include "HighTouchPollingRate.h"
#include "TouchscreenGesture.h"

using ::aidl::vendor::lineage::touch::GloveMode;
using ::aidl::vendor::lineage::touch::HighTouchPollingRate;
using ::aidl::vendor::lineage::touch::TouchscreenGesture;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    LOG(INFO) << "Touch HAL service is starting.";

    std::shared_ptr<GloveMode> gm = ndk::SharedRefBase::make<GloveMode>();
    std::shared_ptr<HighTouchPollingRate> htpr = ndk::SharedRefBase::make<HighTouchPollingRate>();
    std::shared_ptr<TouchscreenGesture> tg = ndk::SharedRefBase::make<TouchscreenGesture>();

    std::string instance = std::string() + GloveMode::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(gm->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    instance = std::string() + HighTouchPollingRate::descriptor + "/default";
    status = AServiceManager_addService(htpr->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    instance = std::string() + TouchscreenGesture::descriptor + "/default";
    status = AServiceManager_addService(tg->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
