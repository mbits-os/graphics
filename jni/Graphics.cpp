#include "jini.hpp"
#include "Log.hpp"

int register_com_mbits_graphics_Movie(JNIEnv*);

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {

	jni::_Env::setVM(vm);

    JNIEnv* env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    register_com_mbits_graphics_Movie(env);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
}
