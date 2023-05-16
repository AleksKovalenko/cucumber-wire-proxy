#ifndef CUCUMBER_TEST_ECHO_CONTAINER_HPP
#define CUCUMBER_TEST_ECHO_CONTAINER_HPP

#include "SupportedTargets.hpp"
#include "protobuf/echo/Echo.hpp"
#include "services/tracer/Tracer.hpp"

namespace application
{
    struct EchoContainer
        : public services::EchoOnConnection
    {
    public:
        EchoContainer(Targets target, services::Tracer& tracer);

        void Detaching() override;

        services::Tracer& tracer;
    };
}

#endif
