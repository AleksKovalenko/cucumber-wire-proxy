#include "DemoSteps.hpp"
#include "services/cucumber/CucumberStepMacro.hpp"
#include <map>
#include <string>
namespace
{
    struct Context
    {
        Context(services::Tracer& tracer)
            : tracer(tracer)
        {}

        public:
        services::Tracer& tracer;
    };

    infra::Optional<Context> context;
}


void InitializeDemoSteps(services::Tracer& tracer)
{
    context.Emplace(tracer);
}

GIVEN("I wait %d seconds test")
{
    auto timeout = *GetUIntegerArgument(0);
    context->tracer.Trace() << "Waiting for " << timeout << " seconds";
    Context().TimeoutTimer().Start(std::chrono::seconds(timeout), [=]() { Success(); });
}