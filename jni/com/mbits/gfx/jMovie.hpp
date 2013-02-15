#ifndef __COM_MBITS_GRAPHICS_MOVIE_HPP__
#define __COM_MBITS_GRAPHICS_MOVIE_HPP__

#include "jini.hpp"
#include "Movie.hpp"
#include "Stream.hpp"
#include "android/graphics/Bitmap.hpp"
#include "android/graphics/Canvas.hpp"

#include <inttypes.h>

namespace com { namespace mbits { namespace graphics {

class Movie;
class MovieClass;

class MovieClass: public jni::Class
{
	friend class Movie;
	
	int m_inited;
	jni::Constructor<jlong> m_constructor;
	jni::Field<jlong> m_native;

	jobject create(gfx::Movie* movie)
	{
		if (!movie) return NULL;
		jobject ret = m_constructor.call(m_class, static_cast<jlong>(reinterpret_cast<uintptr_t>(movie)));
		if (!ret)
			delete movie;

		return ret;
	}

public:
	MovieClass(): m_inited(-1)
	{
	}

	int inited() const { return m_inited; }
	void init()
	{
		JNIEnv* env = jni::_Env::getCurrent();

		static JNINativeMethod sMethods[] = {
		    {"width",            "()I",                                          (void*)width },
		    {"height",           "()I",                                          (void*)height },
		    {"isOpaque",         "()Z",                                          (void*)isOpaque },
		    {"duration",         "()I",                                          (void*)duration },
		    {"setTime",          "(I)Z",                                         (void*)setTime },
		    {"draw",             "(Landroid/graphics/Canvas;FF)V",               (void*)draw },
		    {"decodeStream",     "(Ljava/io/InputStream;)Lcom/mbits/gfx/Movie;", (void*)decodeStream },
		    {"nativeDestructor", "(J)V",                                         (void*)destructor },
		    {"decodeByteArray",  "([BII)Lcom/mbits/gfx/Movie;",                  (void*)decodeByteArray },
		};

		m_inited = -1;

		if (!Class::init(env, "com/mbits/gfx/Movie")) return;
		if (!m_constructor.init(m_class)) return;
		if (!m_native.init(m_class, "mNative")) return;
		m_inited = registerNatives(sMethods);
	}

	jlong mNative(jobject _this) const { return m_native.get(_this); }

	static int width(JNIEnv* env, jobject movie);
	static int height(JNIEnv* env, jobject movie);
	static jboolean isOpaque(JNIEnv* env, jobject movie);
	static int duration(JNIEnv* env, jobject movie);
	static jboolean setTime(JNIEnv* env, jobject movie, int ms);
	static void draw(JNIEnv* env, jobject movie, jobject canvas, jfloat fx, jfloat fy);
	static jobject decodeStream(JNIEnv* env, jobject clazz, jobject istream);
	static jobject decodeByteArray(JNIEnv* env, jobject clazz, jbyteArray byteArray, int offset, int length);
	static void destructor(JNIEnv* env, jobject, gfx::Movie* info) {
	    delete info;
	}
};

class Movie: public jni::Object<MovieClass>
{
	friend class MovieClass;

	static jobject create(gfx::Movie* info)
	{
		return getClass().create(info);
	}
	gfx::Movie* info() const { return (gfx::Movie*)getClass().mNative(m_this); }
public:
	Movie(jobject _this): jni::Object<MovieClass>(_this) {}

	int width() { return info()->width(); }
	int height() { return info()->height(); }
	bool isOpaque() { return info()->isOpaque(); }
	int duration() { return info()->duration(); }
	bool setTime(int ms) { return info()->setTime(ms); }
	void draw(jobject canvas, jfloat fx, jfloat fy);
};

}}} //com::mbits::graphics

#endif //__COM_MBITS_GRAPHICS_MOVIE_HPP__
