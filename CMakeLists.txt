cmake_minimum_required (VERSION 2.6)
project (mongoose)
find_package (Threads)

option (MAIN
    "Compile the main" OFF)

option (EXAMPLES
    "Compile examples" OFF)

option (WEBSOCKET
    "Enables websocket" OFF)

option (CPP_BINDING
    "Enables C++ binding" ON)

option (HAS_JSONCPP
    "Enables JsonCpp" OFF)

option (ENABLE_STATS
    "Enable server statistics" ON)

option (ENABLE_REGEX_URL
    "Enable url regex matching dispatcher" OFF)

option (SHAREDLIB
    "Generate a shared library" OFF)

set (SOURCES
    mongoose.c
    )

set (MONGOOSE_CPP "${PROJECT_SOURCE_DIR}/mongoose")

include_directories ("${PROJECT_SOURCE_DIR}")


if (ENABLE_STATS)
    add_definitions("-DENABLE_STATS")
endif (ENABLE_STATS)

if (ENABLE_REGEX_URL)
    add_definitions("-DENABLE_REGEX_URL")
    SET (CMAKE_CXX_FLAGS "-std=c++11")
endif (ENABLE_REGEX_URL)

if (CPP_BINDING)
    set (SOURCES
        ${SOURCES}
        ${MONGOOSE_CPP}/Utils.cpp
        ${MONGOOSE_CPP}/Controller.cpp
        ${MONGOOSE_CPP}/Mutex.cpp
        ${MONGOOSE_CPP}/Request.cpp
        ${MONGOOSE_CPP}/Response.cpp
        ${MONGOOSE_CPP}/Server.cpp
        ${MONGOOSE_CPP}/Session.cpp
        ${MONGOOSE_CPP}/Sessions.cpp
        ${MONGOOSE_CPP}/StreamResponse.cpp
        ${MONGOOSE_CPP}/UploadFile.cpp
        ${MONGOOSE_CPP}/WebController.cpp
        )

    if (HAS_JSONCPP)
        IF(NOT JSONCPP_DIR)
          message(STATUS "No path for jsonccp as been given")
          set (JSONCPP_DIR "${PROJECT_SOURCE_DIR}/../jsoncpp")
        ENDIF()

        set (SOURCES
            ${SOURCES}
            ${MONGOOSE_CPP}/JsonResponse.cpp
            ${MONGOOSE_CPP}/JsonController.cpp
            )
        message(STATUS "Using ${JSONCPP_DIR}/include and ${JSONCPP_DIR}/lib as jsoncpp path")
        include_directories ("${JSONCPP_DIR}/include/")
        LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${JSONCPP_DIR}/lib/)
    endif (HAS_JSONCPP)

    if (WEBSOCKET)
        set (SOURCES
            ${SOURCES}
            ${MONGOOSE_CPP}/WebSocket.cpp
            ${MONGOOSE_CPP}/WebSockets.cpp
            )
    endif (WEBSOCKET)

    include_directories ("${MONGOOSE_CPP}")
endif (CPP_BINDING)

if (NOT WEBSOCKET)
    add_definitions("-DNO_WEBSOCKET")
endif (NOT WEBSOCKET)

# Adding dl
if (NOT WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} dl)
endif (NOT WIN32)

# Adding sockets for Win32
if (WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
endif (WIN32)

# Compiling library
if (SHAREDLIB)
  add_library (mongoose SHARED ${SOURCES})
else()
  add_library (mongoose ${SOURCES})
endif()

target_link_libraries (mongoose ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})

if (HAS_JSONCPP)
    target_link_libraries (mongoose jsoncpp)
endif (HAS_JSONCPP)

if (EXAMPLES OR MAIN)
    if (HAS_JSONCPP)
      add_subdirectory("${JSONCPP_DIR}" jsoncpp)
    endif (HAS_JSONCPP)
endif ()

# Compiling executable
if (MAIN)
    add_executable (main main.c)
    target_link_libraries (main mongoose)
endif (MAIN)

# Compiling tests
if (EXAMPLES)
    add_executable (post examples/post.c)
    target_link_libraries (post mongoose)

    if (NOT WIN32)
        add_executable (hello examples/hello.c)
            target_link_libraries (hello mongoose)
    endif (NOT WIN32)

    if (CPP_BINDING)
        add_executable (helloworld examples/helloworld.cpp)
        target_link_libraries (helloworld  mongoose)

        add_executable (cpp examples/main.cpp)
        target_link_libraries (cpp  mongoose)

        if (HAS_JSONCPP)
            add_executable (json_api examples/json.cpp)
            target_link_libraries (json_api  mongoose)
        endif (HAS_JSONCPP)

        if (WEBSOCKET)
            add_executable (cpp_websocket examples/websocket.cpp)
            target_link_libraries (cpp_websocket  mongoose)
        endif (WEBSOCKET)
    endif (CPP_BINDING)
endif (EXAMPLES)

# install
set (INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")
configure_file(MongooseConfig.cmake.in MongooseConfig.cmake @ONLY)

install (FILES mongoose.h DESTINATION "${INCLUDE_INSTALL_DIR}")
install (DIRECTORY mongoose DESTINATION "${INCLUDE_INSTALL_DIR}" PATTERN "*.cpp" EXCLUDE)
install (TARGETS mongoose DESTINATION lib EXPORT mongoose-targets)
install (EXPORT mongoose-targets DESTINATION "lib/cmake/mongoose" FILE MongooseTargets.cmake)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/MongooseConfig.cmake DESTINATION "lib/cmake/mongoose")
