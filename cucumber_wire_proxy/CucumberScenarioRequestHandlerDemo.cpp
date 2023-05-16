#include "CucumberScenarioRequestHandlerDemo.hpp"

namespace main_
{
    CucumberScenarioRequestHandlerDemo::CucumberScenarioRequestHandlerDemo(const infra::SharedPtr<application::EchoContainer> echoContainer)
        : echoContainer(echoContainer)
    {}

    void CucumberScenarioRequestHandlerDemo::BeginScenario(const infra::Function<void()>& onDone)
    {
        this->onDone = onDone;
        CucumberScenarioRequestHandler::BeginScenario(onDone);
    }

    void CucumberScenarioRequestHandlerDemo::EndScenario(const infra::Function<void()>& onDone)
    {
        this->onDone = onDone;
        CucumberScenarioRequestHandler::EndScenario(onDone);
    }
}
