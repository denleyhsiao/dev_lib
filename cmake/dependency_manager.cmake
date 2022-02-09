include(FetchContent)

function(declare_dep_module MODULE_NAME)
  if(NOT TARGET ${MODULE_NAME})
    set(options "")
    set(oneValueArgs
      GIT_REPOSITORY
      GIT_TAG
      SOURCE_DIR
    )

    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    FetchContent_Declare(${MODULE_NAME}
      GIT_REPOSITORY  ${ARG_GIT_REPOSITORY}
      GIT_TAG         ${ARG_GIT_TAG}
      SOURCE_DIR      ${ARG_SOURCE_DIR}
      GIT_SHALLOW     TRUE
    )

    fetchcontent_makeavailable(${MODULE_NAME})
  endif()
endfunction(declare_dep_module)
