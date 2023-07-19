#include <iostream>
#include <memory>
#include <string>

#include "../core/Executor.h"
#include "../core/LocalBlock.h"
#include "BatchIterator.h"
#include "CHColumnVector.h"
#include "CHNativeBlock.h"
#include "ExpressionEvaluatorJniWrapper.h"
#include "JniCommon.h"
#include "Query.h"
#include <clickhouse/client.h>

using namespace clickhouse;

static jint jniVersion = JNI_VERSION_1_8;
static std::shared_ptr<Client> client = nullptr;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void * /*reserved*/) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), jniVersion) != JNI_OK) {
        return JNI_ERR;
    }
    /// Initialize client connection.
    client = std::make_shared<Client>(ClientOptions().SetHost("localhost"));
    std::cout << "on load" << std::endl;
    return jniVersion;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
}

JNIEXPORT void JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeInitNative(JNIEnv *, jobject, jbyteArray) {
}

/*
 * Class:     com_ldps_examples_ExpressionEvaluatorJniWrapper
 * Method:    nativeFinalizeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeFinalizeNative(JNIEnv *, jobject) {
}

/*
 * Class:     com_ldps_examples_ExpressionEvaluatorJniWrapper
 * Method:    nativeDoValidate
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeDoValidate(JNIEnv *, jobject, jbyteArray) {
    return false;
}

/*
 * Class:     com_ldps_examples_ExpressionEvaluatorJniWrapper
 * Method:    nativeCreateKernelWithIterator
 * Signature: (J[B[Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeCreateKernelWithIterator(JNIEnv *env, jobject, jlong allocator_id, jbyteArray plan, jobjectArray iter_arr) {
    // TODO like gluten
    jsize plan_size = env->GetArrayLength(plan);
    jbyte *plan_address = env->GetByteArrayElements(plan, nullptr);
    std::string plan_string;
    plan_string.assign(reinterpret_cast<const char *>(plan_address), plan_size);
    std::cout << "sql to execute : " << plan_string << std::endl;

    Executor *executor = new Executor(client);
    executor->selectQuery(plan_string);
    env->ReleaseByteArrayElements(plan, plan_address, JNI_ABORT);
    return reinterpret_cast<jlong>(executor);
}

/*
 * Class:     com_ldps_examples_ExpressionEvaluatorJniWrapper
 * Method:    nativeCreateKernelWithRowIterator
 * Signature: ([B)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeCreateKernelWithRowIterator(JNIEnv *env, jobject, jbyteArray plan) {
    jsize plan_size = env->GetArrayLength(plan);
    jbyte *plan_address = env->GetByteArrayElements(plan, nullptr);
    std::string plan_string;
    plan_string.assign(reinterpret_cast<const char *>(plan_address), plan_size);

    Executor *executor = new Executor(client);
    executor->selectQuery(plan_string);
    env->ReleaseByteArrayElements(plan, plan_address, JNI_ABORT);
    return reinterpret_cast<jlong>(executor);
}

/*
 * Class:     com_ldps_examples_ExpressionEvaluatorJniWrapper
 * Method:    nativeClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ldps_examples_ExpressionEvaluatorJniWrapper_nativeClose(JNIEnv *, jobject, jlong executor_address) {
    Executor *executor = reinterpret_cast<Executor *>(executor_address);
    delete executor;
}

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeHasNext
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_BatchIterator_nativeHasNext(JNIEnv *, jobject, jlong executor_address) {
    Executor *executor = reinterpret_cast<Executor *>(executor_address);
    return executor->hasNext();
}

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeNext
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_ldps_examples_BatchIterator_nativeNext(JNIEnv *, jobject, jlong) {
    // TODO
}

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeCHNext
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_BatchIterator_nativeCHNext(JNIEnv *, jobject, jlong executor_address) {
    Executor *executor = reinterpret_cast<Executor *>(executor_address);
    Block *column_batch = executor->next();
    return reinterpret_cast<Int64>(column_batch);
}

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ldps_examples_BatchIterator_nativeClose(JNIEnv *, jobject, jlong executor_address) {
    // Fixme release here?
    Executor *executor = reinterpret_cast<Executor *>(executor_address);
    delete executor;
}

/*
 * Class:     com_ldps_examples_BatchIterator
 * Method:    nativeFetchMetrics
 * Signature: (J)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_com_ldps_examples_BatchIterator_nativeFetchMetrics(JNIEnv *env, jobject, jlong) {
    // TODO
    jobject native_metrics;
    return native_metrics;
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeHasNull
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_CHColumnVector_nativeHasNull(JNIEnv *, jobject, jlong, jint) {
    // TODO
    return false;
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeNumNulls
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_ldps_examples_CHColumnVector_nativeNumNulls(JNIEnv *, jobject, jlong, jint) {
    // TODO
    return 0;
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeIsNullAt
 * Signature: (IJI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_CHColumnVector_nativeIsNullAt(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    // TODO
    return false;
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetBoolean
 * Signature: (IJI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetBoolean(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return LocalBlock::instance().getBool(block, row_id, column_position);
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetByte
 * Signature: (IJI)B
 */
JNIEXPORT jbyte JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetByte(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return reinterpret_cast<jbyte>(LocalBlock::instance().getByte(block, row_id, column_position));
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetShort
 * Signature: (IJI)S
 */
JNIEXPORT jshort JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetShort(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return reinterpret_cast<jshort>(LocalBlock::instance().getShort(block, row_id, column_position));
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetInt
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetInt(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return LocalBlock::instance().getShort(block, row_id, column_position);
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetLong
 * Signature: (IJI)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetLong(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return LocalBlock::instance().getInt64(block, row_id, column_position);
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetFloat
 * Signature: (IJI)F
 */
JNIEXPORT jfloat JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetFloat(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return LocalBlock::instance().getFloat32(block, row_id, column_position);
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetDouble
 * Signature: (IJI)D
 */
JNIEXPORT jdouble JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetDouble(JNIEnv *, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return LocalBlock::instance().getFloat64(block, row_id, column_position);
}

/*
 * Class:     com_ldps_examples_CHColumnVector
 * Method:    nativeGetString
 * Signature: (IJI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ldps_examples_CHColumnVector_nativeGetString(JNIEnv *env, jobject, jint row_id, jlong block_address, jint column_position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    std::string result = std::move(LocalBlock::instance().getString(block, row_id, column_position));
    return JniCommon::instance().stringTojstring(env, result.c_str());
}

/*
 * Class:     com_ldps_examples_CHNativeBlock
 * Method:    nativeNumRows
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ldps_examples_CHNativeBlock_nativeNumRows(JNIEnv *, jobject, jlong block_address) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return block->GetRowCount();
}

/*
 * Class:     com_ldps_examples_CHNativeBlock
 * Method:    nativeNumColumns
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_ldps_examples_CHNativeBlock_nativeNumColumns(JNIEnv *, jobject, jlong block_address) {
    Block *block = reinterpret_cast<Block *>(block_address);
    return block->GetColumnCount();
}

/*
 * Class:     com_ldps_examples_CHNativeBlock
 * Method:    nativeColumnType
 * Signature: (JI)[B
 */
JNIEXPORT jstring JNICALL Java_com_ldps_examples_CHNativeBlock_nativeColumnType(JNIEnv *env, jobject, jlong block_address, jint position) {
    Block *block = reinterpret_cast<Block *>(block_address);
    ColumnRef col = block->operator[](position);
    std::string colTypeName = col->Type()->GetName();
    return JniCommon::instance().stringTojstring(env, colTypeName.c_str());
}

/*
 * Class:     com_ldps_examples_CHNativeBlock
 * Method:    nativeTotalBytes
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_ldps_examples_CHNativeBlock_nativeTotalBytes(JNIEnv *, jobject, jlong block_address) {
    // TODO
    return 0;
}

/*
 * Class:     com_ldps_examples_CHNativeBlock
 * Method:    nativeClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_ldps_examples_CHNativeBlock_nativeClose(JNIEnv *, jobject, jlong) {
    // TODO
}

JNIEXPORT void JNICALL Java_com_ldps_examples_Query_sqlQuery(JNIEnv *env,
                                                             jobject,
                                                             jstring text) {
    std::string text_string = JniCommon::instance().jstring2string(env, text);
    std::cout << text_string << std::endl;

    //  client->Execute(text_string);

    /// Create a table.
    client->Execute("CREATE TABLE IF NOT EXISTS default.numbers (id UInt64, name "
                    "String) ENGINE = Memory");

    /// Insert some values.
    {
        Block block;

        auto id = std::make_shared<ColumnUInt64>();
        id->Append(1);
        id->Append(7);

        auto name = std::make_shared<ColumnString>();
        name->Append("one");
        name->Append("seven");

        block.AppendColumn("id", id);
        block.AppendColumn("name", name);

        client->Insert("default.numbers", block);
    }

    //    std::shared_ptr<Executor> executor(new Executor(client));
    //    executor->selectQuery(text_string);
    //    // Select values inserted in the previous step.
    //    client->Select("SELECT id, name FROM default.numbers", [](const Block &block) {
    //        for (size_t i = 0; i < block.GetRowCount(); ++i) {
    //            std::cout << block[0]->As<ColumnUInt64>()->At(i) << " "
    //                      << block[1]->As<ColumnString>()->At(i) << "\n";
    //        }
    //    });

    // Delete table.
    //    client->Execute("DROP TABLE default.numbers");
}