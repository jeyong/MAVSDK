#include "log.h"
#include "mavsdk.h"
#include "system_tests_helper.h"
#include "plugins/param/param.h"
#include "plugins/param_server/param_server.h"
<<<<<<< HEAD
=======
//#include "plugins/mavlink_passthrough/mavlink_passthrough.h"
>>>>>>> c6ac28ea (Improve mavlink parameters after split)
#include <chrono>
#include <utility>
#include <vector>
#include <thread>
<<<<<<< HEAD

using namespace mavsdk;

static constexpr unsigned num_params_per_type = 100;

std::vector<std::pair<std::string, float>> generate_float_params()
{
    std::vector<std::pair<std::string, float>> params;

    for (unsigned i = 0; i < num_params_per_type; ++i) {
        params.emplace_back(std::string("TEST_BLA") + std::to_string(i), 42.0f + i);
    }

    return params;
}

std::vector<std::pair<std::string, int>> generate_int_params()
{
    std::vector<std::pair<std::string, int>> params;

    for (unsigned i = 0; i < num_params_per_type; ++i) {
        params.emplace_back(std::string("TEST_FOO") + std::to_string(i), 42.0f + i);
    }

    return params;
}

=======
#include <map>

using namespace mavsdk;

static constexpr unsigned num_params_per_type = 3;

static std::map<std::string, float> generate_float_params()
{
    std::map<std::string, float> params;
    for (unsigned i = 0; i < num_params_per_type; ++i) {
        const auto id = std::string("TEST_FLOAT") + std::to_string(i);
        const float value = 42.0f + i;
        params[id] = value;
    }
    return params;
}

static std::map<std::string, int> generate_int_params()
{
    std::map<std::string, int> params;
    for (unsigned i = 0; i < num_params_per_type; ++i) {
        const auto id = std::string("TEST_INT") + std::to_string(i);
        const int value = 42 + i;
        params[id] = value;
    }
    return params;
}

static std::map<std::string, std::string> generate_string_params()
{
    std::map<std::string, std::string> params;
    for (unsigned i = 0; i < num_params_per_type; ++i) {
        const auto id = std::string("TEST_STRING") + std::to_string(i);
        const std::string value = "VAL" + std::to_string(i);
        params[id] = value;
    }
    return params;
}
// compare originally provided and received values - they have a slightly different data layout.
template<typename T1, typename T2>
static void assert_equal(const std::map<std::string, T1>& values, const std::vector<T2>& received)
{
    EXPECT_EQ(received.size(), values.size());
    // check that all the parameters we got have the right param value
    for (const auto& param : received) {
        EXPECT_EQ(param.value, values.find(param.name)->second);
    }
}

>>>>>>> c6ac28ea (Improve mavlink parameters after split)
TEST(SystemTest, ParamGetAll)
{
    Mavsdk mavsdk_groundstation;
    mavsdk_groundstation.set_configuration(
        Mavsdk::Configuration{Mavsdk::Configuration::UsageType::GroundStation});

    Mavsdk mavsdk_autopilot;
    mavsdk_autopilot.set_configuration(
        Mavsdk::Configuration{Mavsdk::Configuration::UsageType::Autopilot});

    ASSERT_EQ(mavsdk_groundstation.add_any_connection("udp://:17000"), ConnectionResult::Success);
    ASSERT_EQ(
        mavsdk_autopilot.add_any_connection("udp://127.0.0.1:17000"), ConnectionResult::Success);

    auto param_server = ParamServer{
        mavsdk_autopilot.server_component_by_type(Mavsdk::ServerComponentType::Autopilot)};

    auto fut = wait_for_first_system_detected(mavsdk_groundstation);
    ASSERT_EQ(fut.wait_for(std::chrono::seconds(10)), std::future_status::ready);
    auto system = fut.get();

    ASSERT_TRUE(system->has_autopilot());

<<<<<<< HEAD
    auto param = Param{system};

    // Add many params
    for (const auto& float_param : generate_float_params()) {
        EXPECT_EQ(
            param_server.provide_param_float(float_param.first, float_param.second),
            ParamServer::Result::Success);
    }
    for (const auto& int_param : generate_int_params()) {
        EXPECT_EQ(
            param_server.provide_param_int(int_param.first, int_param.second),
            ParamServer::Result::Success);
    }

    auto all_params = param.get_all_params();

    EXPECT_EQ(all_params.float_params.size(), generate_float_params().size());
    EXPECT_EQ(all_params.int_params.size(), generate_int_params().size());
=======
    auto param_sender = Param{system};

    // we emulate a packet loss of every second packet - this obviously doesn't really emulate true
    // packet loss, but will at least test the packet loss resilience a bit. Since the param sender
    // re-transmits up to 2 times, when dropping every second packet everything should still work.
    /*auto drop=std::make_shared<mavsdk::MavlinkPassthrough>(system);
    int drop_in=0;
    int drop_out=0;
    drop->intercept_incoming_messages_async([&drop_in](auto& msg){
        //qDebug()<<"Intercept:Got message"<<msg.msgid;
        drop_in++;
        if(drop_in % 2 ==0)return true;
        return false;
    });
    drop->intercept_outgoing_messages_async([&drop_out](auto& msg){
        drop_out++;
        if(drop_out % 2 ==0)return true;
        return false;
    });*/

    const auto test_float_params = generate_float_params();
    const auto test_int_params = generate_int_params();
    const auto test_string_params = generate_string_params();
    // Add many params (these don't need extended)
    for (auto const& [key, val] : test_float_params) {
        EXPECT_EQ(param_server.provide_param_float(key, val), ParamServer::Result::Success);
    }
    // We also add a couple of std::string parameters - note that they won't show up in
    // get_all_params() when using the non-extended version also note that we add the string
    // parameters before then adding the int params, which also tests if the server handles the
    // "hiding" properly (now the indices of the non-ext params are different to the extended ones).
    for (auto const& [key, val] : test_string_params) {
        EXPECT_EQ(param_server.provide_param_custom(key, val), ParamServer::Result::Success);
    }
    for (auto const& [key, val] : test_int_params) {
        EXPECT_EQ(param_server.provide_param_int(key, val), ParamServer::Result::Success);
    }

    {
        // Here we use the non-extended protocol
        param_sender.late_init(1, false);
        const auto all_params = param_sender.get_all_params();
        assert_equal<int, Param::IntParam>(test_int_params, all_params.int_params);
        assert_equal<float, Param::FloatParam>(test_float_params, all_params.float_params);
    }
    {
        // now we do the same, but this time with the extended protocol
        param_sender.late_init(1, true);
        const auto all_params = param_sender.get_all_params();
        assert_equal<int, Param::IntParam>(test_int_params, all_params.int_params);
        assert_equal<float, Param::FloatParam>(test_float_params, all_params.float_params);
        assert_equal<std::string, Param::CustomParam>(test_string_params, all_params.custom_params);
    }

>>>>>>> c6ac28ea (Improve mavlink parameters after split)
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
