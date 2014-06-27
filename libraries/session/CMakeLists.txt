cmake_minimum_required (VERSION 2.6)
# x11
include_directories(${DIR3PARTY}/x11/include)
link_directories(${DIR3PARTY}/x11/lib)
# boost
include_directories(${DIR3PARTY}/boost/include)
link_directories(${DIR3PARTY}/boost/lib)
# GL
include_directories(${DIR3PARTY}/opengl/include)
link_directories(${DIR3PARTY}/opengl/lib)
# gl-mesa
include_directories(${DIR3PARTY}/gl-mesa/include)
link_directories(${DIR3PARTY}/gl-mesa/lib)
# xcb-glx0
include_directories(${DIR3PARTY}/xcb-glx0/include)
link_directories(${DIR3PARTY}/xcb-glx0/lib)



if(XENO STREQUAL "ON")
  add_definitions(-DXENO)
  include_directories ("/usr/include/xenomai")
  link_directories ("/usr/lib/xenomai")
  
  include_directories ("/usr/xenomai/include")
  link_directories ("/usr/xenomai/lib")
  link_libraries ("pthread")
  link_libraries ("native")
  link_libraries ("rt")
  link_libraries ("analogy")
  link_libraries ("rtdm")
  link_libraries ("xenomai")
endif()
set(CMAKE_CXX_FLAGS_INIT "-Wall --warn-uninitialized --warn-unused-vars '-std=c++0x'")

message(${DIR3PARTY})

# link_directories(${DIR3PARTY}/lib)
link_libraries (glut libX11.a dl xcb xcb-glx)
link_libraries (GL)
link_libraries (GLU)

link_libraries (boost_program_options)

if (STATIC STREQUAL "ON")
  add_library (session session.cc trial.cc shape.cc square.cc rectangle.cc variable.cc setup.cc cross.cc setup.cc window.cc sphere.cc plan.cc  sphereshadow.cc rectangle3d.cc adapt.cc) #square3d.cc aircraft.cc 3ds.cc 3dmodel.cc bmp.cc)
else()
  add_library (session SHARED session.cc trial.cc shape.cc square.cc rectangle.cc variable.cc setup.cc cross.cc setup.cc window.cc sphere.cc  plan.cc  sphereshadow.cc rectangle3d.cc adapt.cc) # square3d.cc  aircraft.cc 3ds.cc 3dmodel.cc bmp.cc )
endif()
target_link_libraries (configuration)
link_libraries(configuration)
link_libraries(driver)
link_libraries(recorder)
link_libraries(textures)
# include_directories(${DIR3PARTY}/include)
add_executable (sessionBin session.cc trial.cc  shape.cc cross.cc square.cc  rectangle.cc variable.cc setup.cc window.cc mainSession.cc sphere.cc plan.cc sphereshadow.cc rectangle3d.cc adapt.cc)# square3d.cc aircraft.cc 3ds.cc 3dmodel.cc bmp.cc)
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/configuration")

install_targets(/lib session)
install(FILES ../includes/session.hh
        DESTINATION /usr/include)

set_property(TARGET session PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
