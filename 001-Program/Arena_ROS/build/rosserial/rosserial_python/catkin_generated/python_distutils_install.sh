#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/dream/Projects/Arena/001-Program/Arena_ROS/src/rosserial/rosserial_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/dream/Projects/Arena/001-Program/Arena_ROS/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/dream/Projects/Arena/001-Program/Arena_ROS/install/lib/python2.7/dist-packages:/home/dream/Projects/Arena/001-Program/Arena_ROS/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/dream/Projects/Arena/001-Program/Arena_ROS/build" \
    "/usr/bin/python2" \
    "/home/dream/Projects/Arena/001-Program/Arena_ROS/src/rosserial/rosserial_python/setup.py" \
     \
    build --build-base "/home/dream/Projects/Arena/001-Program/Arena_ROS/build/rosserial/rosserial_python" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/dream/Projects/Arena/001-Program/Arena_ROS/install" --install-scripts="/home/dream/Projects/Arena/001-Program/Arena_ROS/install/bin"
