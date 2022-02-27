/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.vibrator.service.sake"

#include "Vibrator.h"

#include <log/log.h>

#include <thread>

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

static const std::string kVibratorPath = "/sys/class/leds/vibrator/";
static const std::string kMemPlayPath = kVibratorPath + "mem_play";
static const std::string kIndexPath = kVibratorPath + "index";
static const std::string kDurationPath = kVibratorPath + "duration";
static const std::string kActivatePath = kVibratorPath + "activate";
static const std::string kGainPath = kVibratorPath + "gain";

Vibrator::Vibrator() {
    mMemPlayStream.open(kMemPlayPath);
    if (!mMemPlayStream) {
        ALOGE("failed to open mem_play file");
    }

    mIndexStream.open(kIndexPath);
    if (!mIndexStream) {
        ALOGE("failed to open index file");
    }

    mDurationStream.open(kDurationPath);
    if (!mDurationStream) {
        ALOGE("failed to open duration file");
    }

    mActivateStream.open(kActivatePath);
    if (!mActivateStream) {
        ALOGE("failed to open activate file");
    }

    mGainStream.open(kGainPath);
    if (!mGainStream) {
        ALOGE("failed to open gain file");
    }
}

ndk::ScopedAStatus Vibrator::getCapabilities(int32_t* _aidl_return) {
    *_aidl_return = IVibrator::CAP_ON_CALLBACK | IVibrator::CAP_AMPLITUDE_CONTROL |
                    IVibrator::CAP_PERFORM_CALLBACK;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::off() {
    mActivateStream << 0 << std::flush;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::on(int32_t timeoutMs,
                                const std::shared_ptr<IVibratorCallback>& callback) {
    mIndexStream << 1 << std::flush;
    mDurationStream << timeoutMs << std::flush;
    mActivateStream << 1 << std::flush;

    if (callback != nullptr) {
        std::thread([=] {
            usleep(timeoutMs * 1000);
            callback->onComplete();
        }).detach();
    }

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::perform(Effect effect, EffectStrength es __unused,
                                     const std::shared_ptr<IVibratorCallback>& callback __unused,
                                     int32_t* _aidl_return) {
    long playLengthMs;
    int index;

    switch (effect) {
        case Effect::CLICK:
            index = 3;
            break;
        case Effect::DOUBLE_CLICK:
            index = 5;
            break;
        case Effect::TICK:
            index = 10;
            break;
        case Effect::THUD:
            index = 12;
            break;
        case Effect::POP:
            index = 9;
            break;
        case Effect::HEAVY_CLICK:
            index = 2;
            break;
        default:
            return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
    }

    mMemPlayStream << index << std::flush;
    playLengthMs = 150;

    if (callback != nullptr) {
        std::thread([=] {
            usleep(playLengthMs * 1000);
            callback->onComplete();
        }).detach();
    }

    *_aidl_return = playLengthMs;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::getSupportedEffects(std::vector<Effect>* _aidl_return) {
    *_aidl_return = {Effect::CLICK, Effect::DOUBLE_CLICK, Effect::TICK,
                     Effect::THUD,  Effect::POP,          Effect::HEAVY_CLICK};

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::setAmplitude(float amplitude) {
    if (amplitude <= 0.0f || amplitude > 1.0f)
        return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_ILLEGAL_ARGUMENT));

    mGainStream << (uint8_t)(amplitude * 0xff);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Vibrator::setExternalControl(bool enabled __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::getCompositionDelayMax(int32_t* maxDelayMs __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::getCompositionSizeMax(int32_t* maxSize __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::getSupportedPrimitives(
    std::vector<CompositePrimitive>* supported __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::getPrimitiveDuration(CompositePrimitive primitive __unused,
                                                  int32_t* durationMs __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::compose(const std::vector<CompositeEffect>& composite __unused,
                                     const std::shared_ptr<IVibratorCallback>& callback __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::getSupportedAlwaysOnEffects(std::vector<Effect>* _aidl_return __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::alwaysOnEnable(int32_t id __unused, Effect effect __unused,
                                            EffectStrength strength __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

ndk::ScopedAStatus Vibrator::alwaysOnDisable(int32_t id __unused) {
    return ndk::ScopedAStatus(AStatus_fromExceptionCode(EX_UNSUPPORTED_OPERATION));
}

}  // namespace vibrator
}  // namespace hardware
}  // namespace android
}  // namespace aidl
