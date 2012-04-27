Compiling
=========

If you want to compile the library yourself instead of using the packaged `shim.so`, ensure that you have the entire optware and development toolchain installed on your x86 Synology NAS.

Then compile with

    make all

to create `shim.so` and copy that somewhere (like `/volume1/@appstore/CrashPlan/lib/synology-x86-glibc-2.4-shim.so`).

Installing
==========

You need to have the environment variable `LD_PRELOAD` set to the full path of the library from above on the command that starts CrashPlan, that is the start of the Java runtime.

You can do this in the CrashPlanEngine script, or if you are using the optware package from [PC LOAD LETTER](http://pcloadletter.co.uk/2012/01/30/crashplan-syno-package/), you can inject a check into the start-stop-script that does something like this at the top of the file:

    MACHINE=`uname -m`

and this in the start section:

    if [ $MACHINE = "x86_64" ]; then
      su - crashplan -s /bin/sh -c "LD_PRELOAD=/volume1/@appstore/CrashPlan/lib/synology-x86-glibc-2.4-shim.so ${SYNOPKG_PKGDEST}/bin/CrashPlanEngine start"
    else
      su - crashplan -s /bin/sh -c "${SYNOPKG_PKGDEST}/bin/CrashPlanEngine start"
    fi
