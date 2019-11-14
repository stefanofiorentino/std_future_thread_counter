#include <iostream>
#include <future>

int main()
{
    std::atomic_bool cancellation_condition_met{false};
    std::unique_ptr<std::future<void>> task;

    task = std::make_unique<std::future<void>>(std::async(std::launch::async, [&]
    {
        for (auto it = 0u; it < 10u; it++)
        {
            if (cancellation_condition_met)
            {
                cancellation_condition_met = false;
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "1: " << std::to_string(it) << std::endl;
        }
    }));

    std::this_thread::sleep_for(std::chrono::seconds(5));
    cancellation_condition_met = true;
    while(cancellation_condition_met) {}

    task = std::make_unique<std::future<void>>(std::async(std::launch::async, [&]
    {
        for (auto it = 0u; it < 5u; it++)
        {
            if (cancellation_condition_met)
            {
                cancellation_condition_met = false;
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "2: " << std::to_string(it) << std::endl;
        }
    }));

    return 0;
}