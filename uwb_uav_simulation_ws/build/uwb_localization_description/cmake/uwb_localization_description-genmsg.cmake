# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "uwb_localization_description: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iuwb_localization_description:/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(uwb_localization_description_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_custom_target(_uwb_localization_description_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "uwb_localization_description" "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" ""
)

get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_custom_target(_uwb_localization_description_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "uwb_localization_description" "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uwb_localization_description
)
_generate_msg_cpp(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uwb_localization_description
)

### Generating Services

### Generating Module File
_generate_module_cpp(uwb_localization_description
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uwb_localization_description
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(uwb_localization_description_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(uwb_localization_description_generate_messages uwb_localization_description_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_cpp _uwb_localization_description_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_cpp _uwb_localization_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uwb_localization_description_gencpp)
add_dependencies(uwb_localization_description_gencpp uwb_localization_description_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uwb_localization_description_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uwb_localization_description
)
_generate_msg_eus(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uwb_localization_description
)

### Generating Services

### Generating Module File
_generate_module_eus(uwb_localization_description
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uwb_localization_description
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(uwb_localization_description_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(uwb_localization_description_generate_messages uwb_localization_description_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_eus _uwb_localization_description_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_eus _uwb_localization_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uwb_localization_description_geneus)
add_dependencies(uwb_localization_description_geneus uwb_localization_description_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uwb_localization_description_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uwb_localization_description
)
_generate_msg_lisp(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uwb_localization_description
)

### Generating Services

### Generating Module File
_generate_module_lisp(uwb_localization_description
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uwb_localization_description
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(uwb_localization_description_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(uwb_localization_description_generate_messages uwb_localization_description_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_lisp _uwb_localization_description_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_lisp _uwb_localization_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uwb_localization_description_genlisp)
add_dependencies(uwb_localization_description_genlisp uwb_localization_description_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uwb_localization_description_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uwb_localization_description
)
_generate_msg_nodejs(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uwb_localization_description
)

### Generating Services

### Generating Module File
_generate_module_nodejs(uwb_localization_description
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uwb_localization_description
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(uwb_localization_description_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(uwb_localization_description_generate_messages uwb_localization_description_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_nodejs _uwb_localization_description_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_nodejs _uwb_localization_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uwb_localization_description_gennodejs)
add_dependencies(uwb_localization_description_gennodejs uwb_localization_description_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uwb_localization_description_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description
)
_generate_msg_py(uwb_localization_description
  "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description
)

### Generating Services

### Generating Module File
_generate_module_py(uwb_localization_description
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(uwb_localization_description_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(uwb_localization_description_generate_messages uwb_localization_description_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/uwb_data_raw.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_py _uwb_localization_description_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/projects/uwb_uav_simulation_ws/src/uwb_localization_description/msg/position_data_uwb.msg" NAME_WE)
add_dependencies(uwb_localization_description_generate_messages_py _uwb_localization_description_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(uwb_localization_description_genpy)
add_dependencies(uwb_localization_description_genpy uwb_localization_description_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS uwb_localization_description_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uwb_localization_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/uwb_localization_description
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(uwb_localization_description_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uwb_localization_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/uwb_localization_description
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(uwb_localization_description_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uwb_localization_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/uwb_localization_description
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(uwb_localization_description_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uwb_localization_description)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/uwb_localization_description
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(uwb_localization_description_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/uwb_localization_description
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(uwb_localization_description_generate_messages_py std_msgs_generate_messages_py)
endif()
