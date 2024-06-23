#
# Copyright (C) 2021-2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

ifneq ($(filter sake,$(TARGET_DEVICE)),)

ASUSFW_MOUNT_POINT := $(TARGET_OUT_VENDOR)/asusfw
$(ASUSFW_MOUNT_POINT): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $(ASUSFW_MOUNT_POINT)"
	@mkdir -p $(TARGET_OUT_VENDOR)/asusfw

FACTORY_MOUNT_POINT_SYMLINK := $(TARGET_OUT_VENDOR)/factory
$(FACTORY_MOUNT_POINT_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating $@ link"
	@rm -rf $@
	$(hide) ln -sf /mnt/vendor/persist $@

ALL_DEFAULT_INSTALLED_MODULES += $(ASUSFW_MOUNT_POINT) $(FACTORY_MOUNT_POINT_SYMLINK)

endif
