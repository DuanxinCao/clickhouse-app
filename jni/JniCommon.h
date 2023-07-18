#pragma once

#include "jni.h"
#include <iostream>
#include <string>

#include <clickhouse/client.h>

namespace clickhouse {

class JniCommon {
public:
    static JniCommon &instance() {
        static JniCommon jniCommon;
        return jniCommon;
    }

    std::string jstring2string(JNIEnv *env, jstring jStr);

    jstring stringTojstring(JNIEnv *env, const char *pat);

    jbyteArray stringTojbyteArray(JNIEnv *env, const std::string &str);

private:
    ~JniCommon();
    JniCommon();
};
} // namespace clickhouse
