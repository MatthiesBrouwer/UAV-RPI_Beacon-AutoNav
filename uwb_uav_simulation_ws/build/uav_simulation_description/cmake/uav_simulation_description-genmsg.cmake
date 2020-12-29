# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "uav_simulation_description: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iuav_simulation_description:/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(uav_simulation_description_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_custom_target(_uav_simulation_description_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "uav_simulation_description" "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(uav_simulation_description
  "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uav_simulation_description
)

### Generating Services

### Generating Module File
_generate_module_cpp(uav_simulation_description
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uav_simulation_description
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(uav_simulation_description_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(uav_simulation_description_generate_messages uav_simulation_description_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uav_simulation_description_generate_messages_cpp _uav_simulation_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uav_simulation_description_gencpp)
add_dependencies(uav_simulation_description_gencpp uav_simulation_description_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uav_simulation_description_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(uav_simulation_description
  "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uav_simulation_description
)

### Generating Services

### Generating Module File
_generate_module_eus(uav_simulation_description
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uav_simulation_description
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(uav_simulation_description_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(uav_simulation_description_generate_messages uav_simulation_description_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uav_simulation_description_generate_messages_eus _uav_simulation_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uav_simulation_description_geneus)
add_dependencies(uav_simulation_description_geneus uav_simulation_description_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uav_simulation_description_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(uav_simulation_description
  "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uav_simulation_description
)

### Generating Services

### Generating Module File
_generate_module_lisp(uav_simulation_description
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uav_simulation_description
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(uav_simulation_description_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(uav_simulation_description_generate_messages uav_simulation_description_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uav_simulation_description_generate_messages_lisp _uav_simulation_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uav_simulation_description_genlisp)
add_dependencies(uav_simulation_description_genlisp uav_simulation_description_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uav_simulation_description_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(uav_simulation_description
  "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uav_simulation_description
)

### Generating Services

### Generating Module File
_generate_module_nodejs(uav_simulation_description
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uav_simulation_description
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(uav_simulation_description_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(uav_simulation_description_generate_messages uav_simulation_description_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uav_simulation_description_generate_messages_nodejs _uav_simulation_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uav_simulation_description_gennodejs)
add_dependencies(uav_simulation_description_gennodejs uav_simulation_description_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uav_simulation_description_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(uav_simulation_description
  "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uav_simulation_description
)

### Generating Services

### Generating Module File
_generate_module_py(uav_simulation_description
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uav_simulation_description
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(uav_simulation_description_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(uav_simulation_description_generate_messages uav_simulation_description_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uav_simulation_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uav_simulation_description_generate_messages_py _uav_simulation_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uav_simulation_description_genpy)
add_dependencies(uav_simulation_description_genpy uav_simulation_description_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uav_simulation_description_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uav_simulation_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uav_simulation_description
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(uav_simulation_description_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uav_simulation_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uav_simulation_description
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(uav_simulation_description_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uav_simulation_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uav_simulation_description
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(uav_simulation_description_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uav_simulation_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uav_simulation_description
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(uav_simulation_description_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uav_simulation_description)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uav_simulation_description\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uav_simulation_description
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(uav_simulation_description_generate_messages_py std_msgs_generate_messages_py)
endif()
