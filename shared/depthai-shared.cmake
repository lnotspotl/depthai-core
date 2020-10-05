set(DEPTHAI_SHARED_FOLDER ${CMAKE_CURRENT_LIST_DIR}/depthai-shared)

set(DEPTHAI_SHARED_SOURCES 
    ${DEPTHAI_SHARED_FOLDER}/src/general/data_writer.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/logger/logs_writer.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/stream/stream_info.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/xlink/xlink_wrapper.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/json_helper.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/disparity_luts.cpp
    ${DEPTHAI_SHARED_FOLDER}/src/datatype/DatatypeEnum.cpp
)

set(DEPTHAI_SHARED_PUBLIC_INCLUDE
    ${DEPTHAI_SHARED_FOLDER}/include
    ${DEPTHAI_SHARED_FOLDER}/pipeline_builder/generated
)

set(DEPTHAI_SHARED_3RDPARTY_INCLUDE
    ${DEPTHAI_SHARED_FOLDER}/3rdparty
)

set(DEPTHAI_SHARED_INCLUDE
    ${DEPTHAI_SHARED_FOLDER}/src
)

# Try retriving depthai-shared commit hash
find_package(Git)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY "${DEPTHAI_SHARED_FOLDER}"
        RESULT_VARIABLE DEPTHAI_SHARED_COMMIT_RESULT
        OUTPUT_VARIABLE DEPTHAI_SHARED_COMMIT_HASH
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(${DEPTHAI_SHARED_COMMIT_RESULT} EQUAL 0)
        set(DEPTHAI_SHARED_COMMIT_FOUND TRUE)
    else()
        set(DEPTHAI_SHARED_COMMIT_FOUND FALSE)
    endif()
endif()