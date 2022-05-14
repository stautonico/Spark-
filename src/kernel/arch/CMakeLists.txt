# TODO: Add the proper files to the sources depending on the architecture
set(KERNEL_SOURCES
        ${KERNEL_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/x86/i686/io.cpp

        PARENT_SCOPE
        )