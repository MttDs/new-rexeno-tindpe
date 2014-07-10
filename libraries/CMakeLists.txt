# NOTE:
# -> resourdre = cannot open shared object file: No such file or directory
# $ sudo /sbin/ldconfig -v

cmake_minimum_required (VERSION 2.6)
project (Rexeno)

OPTION(XENO "Build Library with super cool option" ON)
OPTION(STATIC "Build Library with super cool option" OFF)

set(CMAKE_DEBUG_TYPE="DEBUG")
# set(DEBUG "1")

if (DEBUG STREQUAL "1")
  message("DEBUG MODE")
  add_definitions(-DDEBUG)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-uninitialized")
include_directories ("${PROJECT_SOURCE_DIR}/configuration")

## Set 3rdParty root
if(NOT DIR3PARTY)
  set(DIR3PARTY "${PROJECT_SOURCE_DIR}/../3rdParty/linux-ububuntu-12-04-noxeno/target")
endif()

# xcb-glx0
include_directories(${DIR3PARTY}/xcb-glx0/include)
link_directories(${DIR3PARTY}/xcb-glx0/lib)

# boost
include_directories(${DIR3PARTY}/boost/include)
link_directories(${DIR3PARTY}/boost/lib)

# GL
include_directories(${DIR3PARTY}/opengl/include)
link_directories(${DIR3PARTY}/opengl/lib)

# gl-mesa
include_directories(${DIR3PARTY}/gl-mesa/include)
link_directories(${DIR3PARTY}/gl-mesa/lib)

# gl-mesa
include_directories(${DIR3PARTY}/x11/include)
link_directories(${DIR3PARTY}/x11/lib)

include_directories ("${PROJECT_SOURCE_DIR}/session")
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/recorder")
include_directories ("${PROJECT_SOURCE_DIR}/textures")

link_libraries (glut libX11.a libX11-xcb.a dl xcb xcb-glx )

add_subdirectory (configuration)
add_subdirectory (session)
add_subdirectory (driver)
add_subdirectory (recorder)
add_subdirectory (textures)

# add_subdirectory (unitTest)

#if (GUI)
  # the GUIS
  add_subdirectory (interface)
  #add_subdirectory (CreateSession)
#endif()
add_executable(Rexeno main.cc )
target_link_libraries (Rexeno configuration)
target_link_libraries (Rexeno session)
target_link_libraries (Rexeno driver)
target_link_libraries (Rexeno recorder)
target_link_libraries (Rexeno textures)

# link_directories(${DIR3PARTY}/lib)
# include_directories(${DIR3PARTY}/include/xenomai)
# include_directories(${DIR3PARTY}/include)
if(XENO STREQUAL "ON")
  add_definitions(-DXENO)
  include_directories ("/usr/xenomai/include")
  link_directories ("/usr/xenomai/lib")
  link_libraries ("pthread")
  link_libraries ("native")
  link_libraries ("rt")
  link_libraries ("analogy")
  link_libraries ("rtdm")
  link_libraries ("xenomai")
  if(NOT DIR3PARTY)
    set(DIR3PARTY "${PROJECT_SOURCE_DIR}/../../3rdParty/linux-ububuntu-12-04-xeno/target")
  endif()
endif()

# here we add configuration files
add_custom_command(TARGET Rexeno POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/unitTest/"
        $<TARGET_FILE_DIR:Rexeno>)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "~/.rexeno")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "~/.rexeno/trial_types")
add_custom_command(TARGET Rexeno POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/configFiles/"
        "~/.rexeno")
install(FILES includes/rexeno.hh includes/types.hh includes/variable.hh includes/setup.hh includes/order_parser.hh
        DESTINATION /usr/include)
