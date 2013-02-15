About
=====

Graphics is an Android binding for the `gfx` ([see](/mbit-os/gfx)) library.
It started as a replacement for the `android.graphics.Movie` and has
similar API.

Requirements
============

Graphics needs `gfx`, obviously, but also `jini` ([see](/mbits-os/jini))
for the C++ JNI bindings. For building an Android library, you'll need
Android developement environment. This includes:

1. [Android SDK](http://developer.android.com/sdk/index.html)
1. [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html)
1. One of:
   * Eclipse with ADT, or
   * Maven

Building
========

For succesfull build, you'll need working environment, as described
on [Android](http://developer.android.com/sdk/index.html "Android SDK") pages.

First make a common directory for the repos:

    $ mkdir Graphics
    $ cd Graphics

Clone the repositories:

    $ git clone git://github.com/mbits-os/jini.git
    $ git clone git://github.com/mbits-os/gfx.git
    $ git clone git://github.com/mbits-os/graphics.git

**TODO**: *Eclipse/Maven instructions*
