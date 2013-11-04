#PROJECT NAME
project(exploot-server)
cmake_minimum_required(VERSION 2.8)

#EXTERNAL PACKAGES (IRRLICHT)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ENet REQUIRED)
find_package(Threads REQUIRED)
find_package(MySQL REQUIRED)
find_package(MysqlConnector REQUIRED)

#INCLUDES & SRC FILES
include_directories(
    ${BULLET_INCLUDE_DIRS}
    ${INET_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/submodules
)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS include/*.h)
file(GLOB PROTOHDRS submodules/exploot-protobuf/build/*.h)
file(GLOB PROTOSRCS submodules/exploot-protobuf/build/*.cc)

#LINKING AND EXECUTABLE
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${PROTOHDRS} ${PROTOSRCS})
target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES} ${ENET_LIBRARIES} ${PROTOBUF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${MYSQL_LIBRARIES} ${MYSQL_CONNECTOR_LIBRARY})
