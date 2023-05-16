add_library(cucumber_test.echo_instantiation STATIC EXCLUDE_FROM_ALL)

target_include_directories(cucumber_test.echo_instantiation PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(cucumber_test.echo_instantiation PRIVATE
    EchoContainer.cpp
    EchoContainer.hpp
    SupportedTargets.hpp
)

target_link_libraries(cucumber_test.echo_instantiation PUBLIC
    infra.util
    infra.syntax
    protobuf.echo
    services.tracer
)
