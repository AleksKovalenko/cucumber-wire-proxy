#ifndef CUCUMBER_TEST_CUCUMBER_SCENARIO_REQUEST_HANDLER_DEMO
#define CUCUMBER_TEST_CUCUMBER_SCENARIO_REQUEST_HANDLER_DEMO

#include "../echo_instantiation/EchoContainer.hpp"
#include "services/cucumber/CucumberRequestHandlers.hpp"
#include "services/tracer/Tracer.hpp"

namespace main_
{
    class CucumberScenarioRequestHandlerDemo
        : public services::CucumberScenarioRequestHandler
    {
    public:
        explicit CucumberScenarioRequestHandlerDemo(const infra::SharedPtr<application::EchoContainer> echoContainer);

        virtual void BeginScenario(const infra::Function<void()>& onDone) override;
        virtual void EndScenario(const infra::Function<void()>& onDone) override;

    private:
        const infra::SharedPtr<application::EchoContainer> echoContainer;
        infra::AutoResetFunction<void()> onDone;
    };
}

#endif
