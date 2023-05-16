#include "args.hxx"
#include "CucumberScenarioRequestHandlerDemo.hpp"
#include "../step_implementations/DemoSteps.hpp"
#include "hal/generic/FileSystemGeneric.hpp"
#include "hal/generic/SynchronousRandomDataGeneratorGeneric.hpp"
#include "hal/generic/TimerServiceGeneric.hpp"
#include "infra/syntax/JsonFileReader.hpp"
#include "infra/util/Tokenizer.hpp"
#include "services/cucumber/TracingCucumberWireProtocolServer.hpp"
#include "services/network/CertificateConvertor.hpp"
#include "services/network/CertificatesMbedTls.hpp"
#include "services/network/TracingConnectionMbedTls.hpp"
#include "services/network_instantiations/NetworkAdapter.hpp"
#include "services/tracer/TracerOnIoOutputInfrastructure.hpp"

namespace
{
    application::Targets GetSupportedDeviceUnderTest(std::string deviceUnderTest)
    {
        if (deviceUnderTest == "Demo")
            return application::Targets::demo;
        else
            throw std::runtime_error("Supplied device under test not supported: " + deviceUnderTest);
    }

    class SetupTeardownCreator
    {
    public:
            SetupTeardownCreator(application::Targets target)
                : target(target)
            {}

            using CucumberScenarioRequestHandlerCreator = infra::CreatorBase<services::CucumberScenarioRequestHandler, void(const infra::SharedPtr<application::EchoContainer>&, services::Tracer& tracer)>;

            CucumberScenarioRequestHandlerCreator& Creator()
            {
                if(target == application::Targets::demo)
                    return demoSetupTeardownCreator;
                else
                    return defaultSetupTeardownCreator;
            }

    private:
            application::Targets target;

            infra::Creator<services::CucumberScenarioRequestHandler, main_::CucumberScenarioRequestHandlerDemo, void(const infra::SharedPtr<application::EchoContainer>&, services::Tracer& tracer)> demoSetupTeardownCreator
            {
                [](infra::Optional<main_::CucumberScenarioRequestHandlerDemo>& object, const infra::SharedPtr<application::EchoContainer>& container, services::Tracer& tracer)
                    {
                        object.Emplace(container);
                    }
            };

            infra::Creator<services::CucumberScenarioRequestHandler, services::CucumberScenarioRequestHandler, void(const infra::SharedPtr<application::EchoContainer>&, services::Tracer& tracer)> defaultSetupTeardownCreator
            {
                [](infra::Optional<services::CucumberScenarioRequestHandler>& object, const infra::SharedPtr<application::EchoContainer>& container, services::Tracer& tracer)
                    {
                        object.Emplace();
                    }
            };
    };

    void InitializeTestSteps(const infra::SharedPtr<application::EchoContainer>& echoContainer, application::Targets deviceUnderTest, hal::FileSystem& fileSystem, services::ConnectionFactory& connectionFactory, services::NameResolver& nameLookup, services::Tracer& tracer)
    {
        static SetupTeardownCreator setupTeardownCreator(deviceUnderTest);
        static infra::ProxyCreator<services::CucumberScenarioRequestHandler, void(const infra::SharedPtr<application::EchoContainer>&, services::Tracer& tracer)> backgroundSetupTeardownCreator(setupTeardownCreator.Creator(), echoContainer, tracer);
        static main_::TracingCucumberInfrastructure<1024> cucumberInfrastructure(connectionFactory, 90, *backgroundSetupTeardownCreator, tracer);

        InitializeDemoSteps(tracer);
    }
}

int main(int argc, const char* argv[], const char* env[])
{
    std::string toolname = argv[0];
    toolname = toolname.substr(toolname.find_last_of("\\") + 1);
    args::ArgumentParser parser("Cucumber wire proxy " + toolname + "\"" + " is the C++ based proxy communicating data between Cucumber test framework over the wire protocol.");
    parser.Prog(toolname);

    args::Group optionals(parser, "Optional arguments:");
    args::HelpFlag help(optionals, "help", "Display this help menu.", { 'h', "help" });

    try
    {
        parser.ParseCLI(argc, argv);

        auto deviceUnderTest = GetSupportedDeviceUnderTest("Demo");

        static hal::FileSystemGeneric fileSystem;

        static hal::TimerServiceGeneric timerService;
        static main_::TracerOnIoOutputInfrastructure tracing;
        static main_::NetworkAdapter network;

        static services::ConnectionFactoryWithNameResolverImpl::WithStorage<1> connectionFactoryReferenceProduct(network.ConnectionFactory(), network.NameResolver());
        application::EchoContainer container(deviceUnderTest, tracing.tracer);
        infra::SharedPtr<application::EchoContainer> echoContainer { infra::UnOwnedSharedPtr(container)};
        InitializeTestSteps(echoContainer, deviceUnderTest, fileSystem, network.ConnectionFactory(), network.NameResolver(), tracing.tracer);
        network.Run();
    }
    catch (const args::Help&)
    {
        std::cout << parser;
        return 1;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}
