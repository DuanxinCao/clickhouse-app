#include "JniCommon.h"

#include "jni.h"
#include <string>

namespace clickhouse {

JniCommon::JniCommon() {
}

JniCommon::~JniCommon() {
}

std::string JniCommon::jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    jclass string_class = env->GetObjectClass(jStr);
    jmethodID get_bytes = env->GetMethodID(string_class, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray string_jbytes = static_cast<jbyteArray>(
        env->CallObjectMethod(jStr, get_bytes, env->NewStringUTF("UTF-8")));

    size_t length = static_cast<size_t>(env->GetArrayLength(string_jbytes));
    jbyte *p_bytes = env->GetByteArrayElements(string_jbytes, nullptr);

    std::string ret = std::string(reinterpret_cast<char *>(p_bytes), length);
    env->ReleaseByteArrayElements(string_jbytes, p_bytes, JNI_ABORT);

    env->DeleteLocalRef(string_jbytes);
    env->DeleteLocalRef(string_class);
    return ret;
}

jstring JniCommon::stringTojstring(JNIEnv *env, const char *pat) {
    jclass strClass = (env)->FindClass("java/lang/String");
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat),
                              reinterpret_cast<const jbyte *>(pat));
    jstring encoding = (env)->NewStringUTF("UTF-8");
    return static_cast<jstring>(
        (env)->NewObject(strClass, ctorID, bytes, encoding));
}

jbyteArray JniCommon::stringTojbyteArray(JNIEnv * env, const std::string & str)
{
    const auto * ptr = reinterpret_cast<const jbyte *>(str.c_str());
    jbyteArray jarray = env->NewByteArray(str.size());
    env->SetByteArrayRegion(jarray, 0, str.size(), ptr);
    return jarray;
}

} // namespace clickhouse