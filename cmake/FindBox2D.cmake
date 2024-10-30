# cmake/FindBox2D.cmake
include(FindPackageHandleStandardArgs)

# Search for the header
find_path(BOX2D_INCLUDE_DIR box2d/box2d.h
    PATHS
    /usr/include
    /usr/local/include
    /opt/local/include
    ${BOX2D_ROOT}/include
)

# Search for the library
find_library(BOX2D_LIBRARY
    NAMES box2d Box2D
    PATHS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    ${BOX2D_ROOT}/lib
)

# Set BOX2D_FOUND
find_package_handle_standard_args(Box2D DEFAULT_MSG
    BOX2D_LIBRARY BOX2D_INCLUDE_DIR)

# Set the output variables
if(BOX2D_FOUND)
    set(BOX2D_INCLUDE_DIRS ${BOX2D_INCLUDE_DIR})
    set(BOX2D_LIBRARIES ${BOX2D_LIBRARY})
endif()

mark_as_advanced(BOX2D_INCLUDE_DIR BOX2D_LIBRARY)