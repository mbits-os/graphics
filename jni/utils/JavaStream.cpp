/*
 * JavaStream.cpp
 *
 *  Created on: 12-02-2013
 *      Author: Marcin
 */

#include "JavaStream.hpp"
#include <new>

namespace gfx { namespace utils {

	JavaStream::JavaStream(const java::io::InputStream& java, jbyteArray storage)
	: m_env(jni::Env()), m_java(java), m_storage(storage)
	{
		m_capacity = m_env->GetArrayLength(m_storage);
	}

	size_t JavaStream::read(void* buffer, size_t size)
	{
		size_t bytesRead = 0;
		do
		{
			size_t requested = size;
            if (requested > m_capacity)
                requested = m_capacity;

            jint read = m_java.read(m_storage, 0, requested);
            jni::Exception::check();

            if (read < 0) break; //EOF?

            m_env->GetByteArrayRegion(m_storage, 0, read, reinterpret_cast<jbyte*>(buffer));
            jni::Exception::check();

            buffer = (void*)((char*)buffer + read);
            bytesRead += read;
            size -= read;
		} while (size != 0);

		return bytesRead;
	}
	size_t JavaStream::skip(size_t length)
	{
		JNIEnv* env = jni::Env();

		jlong skipped = m_java.skip(length);
		jni::Exception::check();

		if (skipped < 0) skipped = 0;

		return (size_t)skipped;
	}
	void JavaStream::reset()
	{
		m_java.reset();
		jni::Exception::check();
	}

	JavaStream* JavaStream::create(jobject java, jbyteArray storage)
	{
		java::io::InputStream in(java);
		if (!in.instanceOf())
			throw java::lang::IllegalArgumentException();
		return new (std::nothrow) JavaStream(in, storage);
	}

}} //gfx::utils
