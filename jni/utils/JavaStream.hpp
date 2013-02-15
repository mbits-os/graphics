/*
 * JavaStream.h
 *
 *  Created on: 12-02-2013
 *      Author: Marcin
 */

#ifndef JAVASTREAM_HPP_
#define JAVASTREAM_HPP_

#include "Stream.hpp"
#include "java/io/InputStream.hpp"

namespace gfx { namespace utils {

	class JavaStream: public Stream
	{
		JNIEnv* m_env;
		java::io::InputStream m_java;
		jbyteArray m_storage;
		size_t m_capacity;
	public:
		JavaStream(const java::io::InputStream& java, jbyteArray bytes);
		~JavaStream() {}

		size_t read(void*, size_t);
		size_t skip(size_t length);
		void reset();

		static JavaStream* create(jobject, jbyteArray);
	};

}} //gfx::utils

#endif /* JAVASTREAM_HPP_ */
