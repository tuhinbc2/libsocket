LOCAL_PATH := $(call my-dir)

C_SRC := ../C
CPP_SRC := ../C++

define traverse
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call traverse, $(e)))
endef

# VideoEngine Static Lib
include $(CLEAR_VARS)
LOCAL_MODULE := libsocket

LOCAL_CFLAGS := -DANDROID_NDK -Wno-deprecated -DUSE_JNI -fexceptions

ALL_FILE := $(call traverse, $(C_SRC))
ALL_FILE += $(call traverse, $(CPP_SRC))

LOCAL_SRC_FILES := $(filter %.cpp %.c, $(ALL_FILE))
#$(warning $(ALL_FILE))

LOCAL_C_INCLUDES := ../headers/

include $(BUILD_STATIC_LIBRARY)