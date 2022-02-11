/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "audio_amplifier.cs35l45"

/* clang-format off */
#include <hardware/audio_amplifier.h>
#include <hardware/hardware.h>
#include <log/log.h>
#include <tinyalsa/mixer.h>
#include <errno.h>
#include <stdlib.h>
/* clang-format on */

int read_cal_value(const char* path, int* value) {
    FILE* file;
    int ret, val;

    file = fopen(path, "r");
    if (!file) {
        ALOGE("%s: failed to open %s", __func__, path);
        return -EINVAL;
    }

    ret = fscanf(file, "%d", &val);
    if (ret != 1)
        return -EINVAL;

    *value = val;

    fclose(file);

    return 0;
}

bool smartpa_inited = false;

static void adev_crus_smartpa_init(void) {
    struct mixer_ctl* ctl;
    struct mixer* mixer = NULL;
    int spk_cal = 8900;
    int rcv_cal = 9100;
    int retries = 300;
    int rc;

    if (smartpa_inited) return;

    while (!mixer && retries) {
        mixer = mixer_open(0);
        if (mixer) break;

        usleep(100000);

        retries--;
    }

    if (!mixer) {
        ALOGE("%s: Failed to open mixer", __func__);
        return;
    }

    rc = read_cal_value("/vendor/factory/audio/spk_cal_val", &spk_cal);
    if (rc) ALOGE("%s: read spk_cal_r failed, using default %u", __func__, spk_cal);

    ctl = mixer_get_ctl_by_name(mixer, "SPK DSP Set CAL_R");
    if (ctl) mixer_ctl_set_value(ctl, 0, spk_cal);

    ctl = mixer_get_ctl_by_name(mixer, "SPK DSP1 Firmware");
    if (ctl) mixer_ctl_set_enum_by_string(ctl, "Protection");

    ctl = mixer_get_ctl_by_name(mixer, "SPK DSP1 Preload Switch");
    if (ctl) mixer_ctl_set_value(ctl, 0, 1);

    ctl = mixer_get_ctl_by_name(mixer, "SPK DSP1 Boot Switch");
    if (ctl) mixer_ctl_set_value(ctl, 0, 1);

    rc = read_cal_value("/vendor/factory/audio/rcv_cal_val", &rcv_cal);
    if (rc) ALOGE("%s: read rcv_cal_r failed, using default %u", __func__, rcv_cal);

    ctl = mixer_get_ctl_by_name(mixer, "RCV DSP Set CAL_R");
    if (ctl) mixer_ctl_set_value(ctl, 0, rcv_cal);

    ctl = mixer_get_ctl_by_name(mixer, "RCV DSP1 Firmware");
    if (ctl) mixer_ctl_set_enum_by_string(ctl, "Protection");

    ctl = mixer_get_ctl_by_name(mixer, "RCV DSP1 Preload Switch");
    if (ctl) mixer_ctl_set_value(ctl, 0, 1);

    ctl = mixer_get_ctl_by_name(mixer, "RCV DSP1 Boot Switch");
    if (ctl) mixer_ctl_set_value(ctl, 0, 1);

    smartpa_inited = true;
}

static int amp_dev_close(hw_device_t* device) {
    if (device) free(device);

    return 0;
}

static int amp_module_open(const hw_module_t* module, const char* name, hw_device_t** device) {
    if (strcmp(name, AMPLIFIER_HARDWARE_INTERFACE)) {
        ALOGE("%s:%d: %s does not match amplifier hardware interface name\n", __func__, __LINE__,
              name);
        return -ENODEV;
    }

    amplifier_device_t* amp_dev = calloc(1, sizeof(amplifier_device_t));
    if (!amp_dev) {
        ALOGE("%s:%d: Unable to allocate memory for amplifier device\n", __func__, __LINE__);
        return -ENOMEM;
    }

    amp_dev->common.tag = HARDWARE_DEVICE_TAG;
    amp_dev->common.module = (hw_module_t*)module;
    amp_dev->common.version = HARDWARE_DEVICE_API_VERSION(1, 0);
    amp_dev->common.close = amp_dev_close;

    amp_dev->set_input_devices = NULL;
    amp_dev->set_output_devices = NULL;
    amp_dev->enable_output_devices = NULL;
    amp_dev->enable_input_devices = NULL;
    amp_dev->set_mode = NULL;
    amp_dev->output_stream_start = NULL;
    amp_dev->input_stream_start = NULL;
    amp_dev->output_stream_standby = NULL;
    amp_dev->input_stream_standby = NULL;
    amp_dev->set_parameters = NULL;
    amp_dev->out_set_parameters = NULL;
    amp_dev->in_set_parameters = NULL;
    amp_dev->set_feedback = NULL;

    adev_crus_smartpa_init();

    *device = (hw_device_t*)amp_dev;

    return 0;
}

/* clang-format off */
static struct hw_module_methods_t hal_module_methods = {
        .open = amp_module_open,
};

amplifier_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AMPLIFIER_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AMPLIFIER_HARDWARE_MODULE_ID,
        .name = "CS35L45 Audio Amplifier HAL",
        .author = "The LineageOS Project",
        .methods = &hal_module_methods,
    },
};
