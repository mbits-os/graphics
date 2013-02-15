LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := gfx

LOCAL_LDLIBS += -llog

LOCAL_SRC_FILES := ../../external/gfx/src/MemoryStream.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/Movie.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/MovieDecoder.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/gif/Decoder.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/gif/Gif.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/gif/GifDecoder.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/gif/GifMovie.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/gif/LzwDecoder.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/gfx/inc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/jini/includes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/jini/code

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := jini

LOCAL_LDLIBS += -llog

LOCAL_SRC_FILES := ../../external/jini/code/android/graphics/Bitmap.cpp
LOCAL_SRC_FILES += ../../external/jini/src/jini.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../external/jini/includes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/jini/code

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := Graphics

LOCAL_LDLIBS += -llog -ljnigraphics

LOCAL_SRC_FILES := Graphics.cpp
LOCAL_SRC_FILES += com/mbits/gfx/jMovie.cpp
LOCAL_SRC_FILES += ../../external/gfx/src/JavaBitmap.cpp
LOCAL_SRC_FILES += utils/JavaStream.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/jini/includes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/jini/code
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../external/gfx/inc

LOCAL_STATIC_LIBRARIES := gfx
LOCAL_STATIC_LIBRARIES += jini

include $(BUILD_SHARED_LIBRARY)
