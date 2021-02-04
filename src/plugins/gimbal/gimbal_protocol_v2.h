#pragma once

#include "plugins/gimbal/gimbal.h"
#include "gimbal_protocol_base.h"

namespace mavsdk {

class GimbalProtocolV2 : public GimbalProtocolBase {
public:
    GimbalProtocolV2(
        SystemImpl& system_impl,
        const mavlink_gimbal_manager_information_t& information,
        uint8_t gimbal_manager_sysid,
        uint8_t gimbal_manager_compid);
    ~GimbalProtocolV2() = default;

    Gimbal::Result set_pitch_and_yaw(float pitch_deg, float yaw_deg) override;
    void set_pitch_and_yaw_async(
        float pitch_deg, float yaw_deg, Gimbal::ResultCallback callback) override;

    Gimbal::Result
    set_pitch_rate_and_yaw_rate(float pitch_rate_deg_s, float yaw_rate_deg_s) override;

    void set_pitch_rate_and_yaw_rate_async(
        float pitch_rate_deg_s, float yaw_rate_deg_s, Gimbal::ResultCallback callback) override;

    Gimbal::Result set_mode(const Gimbal::GimbalMode gimbal_mode) override;
    void
    set_mode_async(const Gimbal::GimbalMode gimbal_mode, Gimbal::ResultCallback callback) override;

    Gimbal::Result
    set_roi_location(double latitude_deg, double longitude_deg, float altitude_m) override;
    void set_roi_location_async(
        double latitude_deg,
        double longitude_deg,
        float altitude_m,
        Gimbal::ResultCallback callback) override;

    Gimbal::Result take_control(Gimbal::ControlMode control_mode) override;
    void
    take_control_async(Gimbal::ControlMode control_mode, Gimbal::ResultCallback callback) override;

    Gimbal::Result release_control() override;
    void release_control_async(Gimbal::ResultCallback callback) override;

    Gimbal::ControlMode control() override;
    void control_async(Gimbal::ControlCallback callback) override;

private:
<<<<<<< HEAD
    void set_gimbal_information(const mavlink_gimbal_manager_information_t& information);
    void process_gimbal_manager_status(const mavlink_message_t& message);
=======
    uint8_t _gimbal_manager_sysid;
    uint8_t _gimbal_manager_compid;
    uint8_t _gimbal_device_id;
>>>>>>> develop

    Gimbal::GimbalMode _gimbal_mode{Gimbal::GimbalMode::YawFollow};

    Gimbal::ControlMode _current_control_mode = Gimbal::ControlMode::None;
    Gimbal::ControlCallback _control_callback;

    std::condition_variable _control_thread_cv;
    std::mutex _control_thread_mutex;
    bool _is_mavlink_manager_status_registered = false;
};

} // namespace mavsdk
