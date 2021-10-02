#
# Copyright (C) 2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LIBEGL_SYMLINK := $(TARGET_OUT_VENDOR)/lib/libEGL_adreno.so
$(LIBEGL_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib/libEGL_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

LIBEGL64_SYMLINK := $(TARGET_OUT_VENDOR)/lib64/libEGL_adreno.so
$(LIBEGL64_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib64/libEGL_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

LIBGLES_SYMLINK := $(TARGET_OUT_VENDOR)/lib/libGLESv2_adreno.so
$(LIBGLES_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib/libGLESv2_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

LIBGLES64_SYMLINK := $(TARGET_OUT_VENDOR)/lib64/libGLESv2_adreno.so
$(LIBGLES64_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib64/libGLESv2_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

LIBQ3DTOOLS_SYMLINK := $(TARGET_OUT_VENDOR)/lib/libq3dtools_adreno.so
$(LIBQ3DTOOLS_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib/libq3dtools_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

LIBQ3DTOOLS64_SYMLINK := $(TARGET_OUT_VENDOR)/lib64/libq3dtools_adreno.so
$(LIBQ3DTOOLS64_SYMLINK): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating lib64/libq3dtools_adreno.so symlink: $@"
	@mkdir -p $(dir $@)
	$(hide) ln -sf egl/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += \
	$(LIBEGL_SYMLINK) \
	$(LIBEGL64_SYMLINK) \
	$(LIBGLES_SYMLINK) \
	$(LIBGLES64_SYMLINK) \
	$(LIBQ3DTOOLS_SYMLINK) \
	$(LIBQ3DTOOLS64_SYMLINK)
