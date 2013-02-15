#include "jini.hpp"
#include "Movie.hpp"
#include "Stream.hpp"
#include "MemoryStream.hpp"
#include "android/graphics/Bitmap.hpp"
#include "android/graphics/Canvas.hpp"
#include "com/mbits/gfx/jMovie.hpp"
#include "utils/JavaStream.hpp"

#include <inttypes.h>

namespace com { namespace mbits { namespace graphics {

	int MovieClass::width(JNIEnv* env, jobject movie)
	{
		try {
			NPE_CHECK(movie);
			return Movie(movie).width();
		} catch(jni::Exception&) {}
		return 0;
	}

	int MovieClass::height(JNIEnv* env, jobject movie)
	{
	    try {
	    	NPE_CHECK(movie);
	    	return Movie(movie).height();
	    } catch(jni::Exception&) {}
	    return 0;
	}

	jboolean MovieClass::isOpaque(JNIEnv* env, jobject movie)
	{
	    try {
	    	NPE_CHECK(movie);
	    	return Movie(movie).isOpaque();
	    } catch(jni::Exception&) {}
	    return false;
	}

	int MovieClass::duration(JNIEnv* env, jobject movie)
	{
	    try {
	    	NPE_CHECK(movie);
	    	return Movie(movie).duration();
	    } catch(jni::Exception&) {}
	    return 0;
	}

	jboolean MovieClass::setTime(JNIEnv* env, jobject movie, int ms)
	{
	    try {
	    	NPE_CHECK(movie);
	    	return Movie(movie).setTime(ms);
	    } catch(jni::Exception&) {}
	    return false;
	}

	void MovieClass::draw(JNIEnv* env, jobject movie, jobject canvas,
	                       jfloat fx, jfloat fy)
	{
	    try {
	    	NPE_CHECK(movie);
	    	NPE_CHECK(canvas);

	    	Movie(movie).draw(canvas, fx, fy);
	    } catch(jni::Exception&) {}
	}

	jobject MovieClass::decodeStream(JNIEnv* env, jobject clazz, jobject istream)
	{
	    try
	    {
	    	NPE_CHECK(istream);
			jbyteArray byteArray = env->NewByteArray(16*1024);
			gfx::Stream* strm = gfx::utils::JavaStream::create(istream, byteArray);
			if (NULL == strm)
				return 0;

			gfx::Movie* moov = gfx::Movie::decodeStream(strm);
			delete strm;

			return Movie::create(moov);
	    }
	    catch (jni::Exception&) {}

	    return NULL;
	}

	jobject MovieClass::decodeByteArray(JNIEnv* env, jobject clazz,
			jbyteArray byteArray, int offset, int length)
	{

	    try
	    {
	    	NPE_CHECK(byteArray);
			int totalLength = env->GetArrayLength(byteArray);
			if ((offset | length) < 0 || offset + length > totalLength)
			{
				throw java::lang::ArrayIndexOutOfBoundsException();
				return 0;
			}

		    JavaArray<jbyte> array(env, byteArray);
		    gfx::Stream* strm = gfx::MemoryStream::create(array.ptr() + offset, length);
		    if (NULL == strm)
		        return 0;

		    gfx::Movie* moov = gfx::Movie::decodeStream(strm);
		    delete strm;

		    return Movie::create(moov);
	    }
	    catch (jni::Exception&) {}

	    return NULL;
	}

	using android::graphics::Canvas;
	using android::graphics::Bitmap;
	using android::graphics::Paint;

	void Movie::draw(jobject canvas, float fx, float fy)
	{
		gfx::Bitmap& bitmap = info()->bitmap();
		jni::Exception::check();

		if (bitmap.backing()._this())
		{
			Canvas(canvas).drawBitmap(bitmap.backing(), fx, fy, NULL);
			jni::Exception::check();
		}
	}

}}} //com::mbits::graphics

int register_com_mbits_graphics_Movie(JNIEnv*)
{
	return com::mbits::graphics::Movie::init();
}
