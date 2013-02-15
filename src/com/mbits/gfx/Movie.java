package com.mbits.gfx;

import java.io.FileInputStream;
import java.io.InputStream;

import android.graphics.Canvas;

public class Movie {
    private final long mNative;
    
    private Movie(long nativeObject) {
        if (nativeObject == 0) {
            throw new RuntimeException("native movie creation failed");
        }
        mNative = nativeObject;
    }

    public native int width();
    public native int height();
    public native boolean isOpaque();
    public native int duration();

    public native boolean setTime(int relativeMilliseconds);    

    public native void draw(Canvas canvas, float x, float y);
    
    public static native Movie decodeStream(InputStream is);
    public static native Movie decodeByteArray(byte[] data, int offset,
                                               int length);

    private static native void nativeDestructor(long nativeObject);

    public static Movie decodeFile(String pathName) {
        InputStream is;
        try {
            is = new FileInputStream(pathName);
        }
        catch (java.io.FileNotFoundException e) {
            return null;
        }
        return decodeTempStream(is);
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            nativeDestructor(mNative);
        } finally {
            super.finalize();
        }
    }

    private static Movie decodeTempStream(InputStream is) {
        Movie moov = null;
        try {
            moov = decodeStream(is);
            is.close();
        }
        catch (java.io.IOException e) {
            /*  do nothing.
                If the exception happened on open, moov will be null.
                If it happened on close, moov is still valid.
            */
        }
        return moov;
    }

    static {
    	System.loadLibrary("Graphics");
    }
}
