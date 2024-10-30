#cmake/FindLibTorch.cmake
set(TORCH_ROOT "" CACHE PATH "Path to LibTorch installation")

find_path(TORCH_INCLUDE_DIRS torch/torch.h
    PATHS
    ${TORCH_ROOT}/include
    ${TORCH_ROOT}/include/torch/csrc/api/include
)

if(WIN32)
    find_library(TORCH_LIBRARIES torch
        PATHS
        ${TORCH_ROOT}/lib
    )
else()
    find_library(TORCH_LIBRARIES torch
        PATHS
        ${TORCH_ROOT}/lib
    )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibTorch DEFAULT_MSG
    TORCH_LIBRARIES
    TORCH_INCLUDE_DIRS
)

mark_as_advanced(TORCH_INCLUDE_DIRS TORCH_LIBRARIES)