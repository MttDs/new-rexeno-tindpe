include_directories("/usr/include/qt4")
include_directories(view)
include_directories(includes)

MESSAGE(${DIR3PARTY}/qt)
SET(QT_ROOT_DIR ${DIR3PARTY}/qt)

find_package(Qt4 REQUIRED)
link_libraries(QtCore)
link_libraries(QtGui)

find_package(Boost COMPONENTS system filesystem REQUIRED)
link_libraries(${Boost_FILESYSTEM_LIBRARY})
link_libraries(${Boost_SYSTEM_LIBRARY})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

qt4_wrap_cpp(TrialCreator_MOC includes/create_protocole.hh includes/mainwindow.hh  includes/ui_mainwindow.hh includes/controller.hh  )#view/popup.hh )
#qt4_wrap_cpp(TrialCreator_Popup includes/view.hh view/popup.hh)
add_executable(TrialCreator ${TrialCreator_MOC} main.cc view/create_protocole.cc controller/controller.cc view/mainwindow.cc)#model/model.cc  controler/controler.cc view/view.cc  )#view/popup.cc)
target_link_libraries(TrialCreator ${QT_LIBRARIES})
