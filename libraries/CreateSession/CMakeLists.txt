link_directories(${DIR3PARTY})
#link_libraries (glut)
link_libraries (libglut.a libX11.a dl xcb)
link_libraries (boost_program_options)

#include_directories("/usr/include/qt4")
include_directories($(DIR3PARTY)/include)
include_directories(view)
include_directories(includes)
SET(QT_ROOT_DIR ${DIR3PARTY}/qt)
find_package(Qt4 REQUIRED)
link_libraries(QtCore)
link_libraries(QtGui)

find_package(Boost COMPONENTS system filesystem REQUIRED)
link_libraries(${Boost_FILESYSTEM_LIBRARY})
link_libraries(${Boost_SYSTEM_LIBRARY})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

qt4_wrap_cpp(SessionCreator_MOC includes/view.hh view/SessionCreator.hh)
add_executable(SessionCreator model/model.cc SessionCreator.cc  view/view.cc  ${SessionCreator_MOC})
target_link_libraries(SessionCreator ${QT_LIBRARIES})

# controler/controler.cc
