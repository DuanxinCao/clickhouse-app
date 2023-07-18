/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ldps_examples_BatchIterator */

#ifndef _Included_com_ldps_examples_BatchIterator
#define _Included_com_ldps_examples_BatchIterator
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeHasNext
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_BatchIterator_nativeHasNext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeNext
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_ldps_examples_BatchIterator_nativeNext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeCHNext
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_BatchIterator_nativeCHNext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ldps_examples_BatchIterator_nativeClose
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeFetchMetrics
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_ldps_examples_BatchIterator_nativeFetchMetrics
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif