# xcb-glx0
include_directories(${DIR3PARTY}/xcb-glx0/include)
link_directories(${DIR3PARTY}/xcb-glx0/lib)
# boost
include_directories(${DIR3PARTY}/boost/include/boost)
link_directories(${DIR3PARTY}/boost/lib)
# link_libraries (glut)
link_libraries (boost_program_options)

add_subdirectory (session)
