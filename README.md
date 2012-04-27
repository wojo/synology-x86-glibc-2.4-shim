Description
===========

On Synology NAS units running DSM 4.0 on x86 platforms the glibc version utilized 2.3.6. This is detected by CrashPlan as an unsupported version and disables support for the real-time filesystem watcher.

This stub can be used to intercept calls to the `gnu_get_libc_version` function to fool CrashPlan into think we are on glibc 2.4 and also implements the userspace inotify functions to add and remove watches. 

Compiling
=========

If you want to compile the library yourself instead of using the packaged `shim.so`, ensure that you have the entire optware and development toolchain installed on your x86 Synology NAS.

Then compile with

    make all

to create `shim.so` and copy that somewhere (like `/volume1/@appstore/CrashPlan/lib/synology-x86-glibc-2.4-shim.so`).

Installing
==========

Set the environment variable `LD_PRELOAD` to the full path of the library compiled on the command that starts CrashPlan (that is the start of the Java runtime).

You can do this in the CrashPlanEngine script or if you are using the optware package from [PC LOAD LETTER](http://pcloadletter.co.uk/2012/01/30/crashplan-syno-package/), you can inject a check into the start-stop-script that does something like this at the top of the file:

    MACHINE=`uname -m`

and this in the start section:

    if [ $MACHINE = "x86_64" ]; then
      su - crashplan -s /bin/sh -c "LD_PRELOAD=/volume1/@appstore/CrashPlan/lib/synology-x86-glibc-2.4-shim.so ${SYNOPKG_PKGDEST}/bin/CrashPlanEngine start"
    else
      su - crashplan -s /bin/sh -c "${SYNOPKG_PKGDEST}/bin/CrashPlanEngine start"
    fi

Verifying Operation
===================

Checking the `/volume1/@appstore/CrashPlan/log/service.log.0` should reveal that inotify support was enabled. Without this shim, you'll get an exception citing that glibc 2.3.6 is too old and that inotify has been turned off.

Of course this can also be verified by loading the CrashPlan GUI and causing file operations (creating a file) and watching the # of files in the todo section. It should reflect changes made to the filesystem within a few hundred milliseconds. 
