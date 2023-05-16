if (EMIL_HOST_BUILD)
    add_executable(cucumber_test.cucumber_wire_proxy)

    target_include_directories(cucumber_test.cucumber_wire_proxy PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

    target_sources(cucumber_test.cucumber_wire_proxy PRIVATE
        Main.cpp
        CucumberScenarioRequestHandlerDemo.cpp
        CucumberScenarioRequestHandlerDemo.hpp
    )


    target_link_libraries(cucumber_test.cucumber_wire_proxy PUBLIC
        infra.util
        infra.syntax
        cucumber_test.step_implementations
        services.cucumber
        services.util
        hal.generic
        args
        services.network_instantiations
    )
endif()
