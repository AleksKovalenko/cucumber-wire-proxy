add_library(cucumber_test.step_implementations STATIC EXCLUDE_FROM_ALL)

target_include_directories(cucumber_test.step_implementations PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(cucumber_test.step_implementations PRIVATE
    DemoSteps.cpp
    DemoSteps.hpp
)

target_link_libraries(cucumber_test.step_implementations PUBLIC
    cucumber_test.echo_instantiation
    services.cucumber
)
