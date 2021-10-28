/*
 * Copyright (C) 2021 The Android Open Source Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/android/hardware/light/BnLights.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android-base/file.h>
#include <android-base/logging.h>

using aidl::android::hardware::light::BnLights;
using aidl::android::hardware::light::HwLight;
using aidl::android::hardware::light::HwLightState;
using aidl::android::hardware::light::ILights;
using aidl::android::hardware::light::LightType;
using android::base::WriteStringToFile;
using ndk::ScopedAStatus;
using ndk::SharedRefBase;

char const* const GREEN_LED_FILE = "/sys/class/leds/green/brightness";
char const* const RED_LED_FILE = "/sys/class/leds/red/brightness";

class Lights : public BnLights {
  private:
    std::vector<HwLight> availableLights;

    void addLight(LightType const type, int const ordinal) {
        HwLight light{};
        light.id = availableLights.size();
        light.type = type;
        light.ordinal = ordinal;
        availableLights.emplace_back(light);
    }

  public:
    Lights() : BnLights() {
        addLight(LightType::BACKLIGHT, 0);
        addLight(LightType::KEYBOARD, 0);
        addLight(LightType::BUTTONS, 0);
        addLight(LightType::BATTERY, 0);
        addLight(LightType::NOTIFICATIONS, 0);
        addLight(LightType::ATTENTION, 0);
        addLight(LightType::BLUETOOTH, 0);
        addLight(LightType::WIFI, 0);
    }

    ScopedAStatus getLights(std::vector<HwLight>* lights) override {
        for (auto i = availableLights.begin(); i != availableLights.end(); i++) {
            lights->push_back(*i);
        }

        return ScopedAStatus::ok();
    }

    ScopedAStatus setLightState(int id, const HwLightState&) override {
        if (!(0 <= id && id < availableLights.size())) {
            return ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
        }

        HwLight const& light = availableLights[id];

        switch (light.type) {
            case LightType::BATTERY:
                WriteStringToFile("255", RED_LED_FILE);
                break;
            case LightType::NOTIFICATIONS:
                WriteStringToFile("255", GREEN_LED_FILE);
                break;
            default:
                break;
        }

        return ScopedAStatus::ok();
    }
};

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    std::shared_ptr<Lights> light = SharedRefBase::make<Lights>();

    const std::string instance = std::string() + ILights::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(light->asBinder().get(), instance.c_str());

    if (status != STATUS_OK) {
        LOG(ERROR) << "Could not register" << instance;
    }

    ABinderProcess_joinThreadPool();

    return 1;
}
