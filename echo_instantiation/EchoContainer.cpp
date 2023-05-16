#include "EchoContainer.hpp"

namespace application
{
    EchoContainer::EchoContainer(Targets target, services::Tracer& tracer)
        : tracer(tracer)
    {}

    void EchoContainer::Detaching()
    {
        tracer.Trace() << "EchoContainer::Detaching(): connection lost";

        // Not so gracefuly closing communication with cucumber ruby
        std::exit(EXIT_FAILURE);
    }
}
