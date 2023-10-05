/* ==== Application Includes =============================================== */
#include "serial_interface/vmx_serial_if.h"

/* ==== Standard Library Includes ========================================== */
#include <chrono>
#include <memory>

/* ==== Open Source Includes =============================================== */
#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include <vmx/WindowsVolumeMixer.h>

/* ==== Functions ========================================================== */
int
throwableMain
(
    int     argc,
    char   *argv[]
)
{
    CLI::App        cli{"vmx serial observer host v1.0"};
    auto            pMixer = std::make_unique<vmx::WindowsVolumeMixer>();
    unsigned int    peakSamplingPeriodMillis = 125u;

    // Command line options
    cli.add_option("-p,--peakSamplingPeriod", peakSamplingPeriodMillis, "Sampling period for peak meters in milliseconds; 0 indicates no sampling");
    CLI11_PARSE(cli, argc, argv);

    // Mixer setup
    pMixer->setPeakSamplingPeriod(std::chrono::milliseconds(peakSamplingPeriodMillis));

    return EXIT_SUCCESS;
}

/**
 * @brief      Process entry point
 *
 * @param[in]  argc  The count of CLI arguments
 * @param      argv  The CLI arguments array
 *
 * @return     EXIT_SUCCESS on successful process termination
 *             EXIT_FAILURE if process terminates with error
 */
int
main
(
    int     argc,
    char   *argv[]
)
{
    try
    {
        return throwableMain(argc, argv);
    }
    catch(std::exception e)
    {
        fmt::print("{}\n", e.what());
    }
    catch(...)
    {
        fmt::print("Unknown exception type caught. {}:{}\n", __FILE__, __LINE__);
    }

    return EXIT_FAILURE;
}
