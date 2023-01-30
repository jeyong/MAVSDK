// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/transponder/transponder.proto)

#include <iomanip>

#include "transponder_impl.h"
#include "plugins/transponder/transponder.h"

namespace mavsdk {

using AdsbVehicle = Transponder::AdsbVehicle;



Transponder::Transponder(System& system) : PluginBase(), _impl{std::make_unique<TransponderImpl>(system)} {}

Transponder::Transponder(std::shared_ptr<System> system) : PluginBase(), _impl{std::make_unique<TransponderImpl>(system)} {}

Transponder::~Transponder() {}



void Transponder::subscribe_transponder(TransponderCallback callback)
{
    _impl->subscribe_transponder(callback);
}




Transponder::AdsbVehicle
Transponder::transponder() const
{
    return _impl->transponder();
}



void Transponder::set_rate_transponder_async(double rate_hz, const ResultCallback callback)
{
    _impl->set_rate_transponder_async(rate_hz, callback);
}



Transponder::Result Transponder::set_rate_transponder(double rate_hz) const
{
    return _impl->set_rate_transponder(rate_hz);
}



bool operator==(const Transponder::AdsbVehicle& lhs, const Transponder::AdsbVehicle& rhs)
{
    return
        (rhs.icao_address == lhs.icao_address) &&
        ((std::isnan(rhs.latitude_deg) && std::isnan(lhs.latitude_deg)) || rhs.latitude_deg == lhs.latitude_deg) &&
        ((std::isnan(rhs.longitude_deg) && std::isnan(lhs.longitude_deg)) || rhs.longitude_deg == lhs.longitude_deg) &&
        ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) || rhs.absolute_altitude_m == lhs.absolute_altitude_m) &&
        ((std::isnan(rhs.heading_deg) && std::isnan(lhs.heading_deg)) || rhs.heading_deg == lhs.heading_deg) &&
        ((std::isnan(rhs.horizontal_velocity_m_s) && std::isnan(lhs.horizontal_velocity_m_s)) || rhs.horizontal_velocity_m_s == lhs.horizontal_velocity_m_s) &&
        ((std::isnan(rhs.vertical_velocity_m_s) && std::isnan(lhs.vertical_velocity_m_s)) || rhs.vertical_velocity_m_s == lhs.vertical_velocity_m_s) &&
        (rhs.callsign == lhs.callsign) &&
        (rhs.emitter_type == lhs.emitter_type) &&
        (rhs.squawk == lhs.squawk) &&
        (rhs.tslc_s == lhs.tslc_s);
}

std::ostream& operator<<(std::ostream& str, Transponder::AdsbVehicle const& adsb_vehicle)
{
    str << std::setprecision(15);
    str << "adsb_vehicle:" << '\n'
        << "{\n";
    str << "    icao_address: " << adsb_vehicle.icao_address << '\n';
    str << "    latitude_deg: " << adsb_vehicle.latitude_deg << '\n';
    str << "    longitude_deg: " << adsb_vehicle.longitude_deg << '\n';
    str << "    absolute_altitude_m: " << adsb_vehicle.absolute_altitude_m << '\n';
    str << "    heading_deg: " << adsb_vehicle.heading_deg << '\n';
    str << "    horizontal_velocity_m_s: " << adsb_vehicle.horizontal_velocity_m_s << '\n';
    str << "    vertical_velocity_m_s: " << adsb_vehicle.vertical_velocity_m_s << '\n';
    str << "    callsign: " << adsb_vehicle.callsign << '\n';
    str << "    emitter_type: " << adsb_vehicle.emitter_type << '\n';
    str << "    squawk: " << adsb_vehicle.squawk << '\n';
    str << "    tslc_s: " << adsb_vehicle.tslc_s << '\n';
    str << '}';
    return str;
}



std::ostream& operator<<(std::ostream& str, Transponder::Result const& result)
{
    switch (result) {
        case Transponder::Result::Unknown:
            return str << "Unknown";
        case Transponder::Result::Success:
            return str << "Success";
        case Transponder::Result::NoSystem:
            return str << "No System";
        case Transponder::Result::ConnectionError:
            return str << "Connection Error";
        case Transponder::Result::Busy:
            return str << "Busy";
        case Transponder::Result::CommandDenied:
            return str << "Command Denied";
        case Transponder::Result::Timeout:
            return str << "Timeout";
        default:
            return str << "Unknown";
    }
}



std::ostream& operator<<(std::ostream& str, Transponder::AdsbEmitterType const& adsb_emitter_type)
{
    switch (adsb_emitter_type) {
        case Transponder::AdsbEmitterType::NoInfo:
            return str << "No Info";
        case Transponder::AdsbEmitterType::Light:
            return str << "Light";
        case Transponder::AdsbEmitterType::Small:
            return str << "Small";
        case Transponder::AdsbEmitterType::Large:
            return str << "Large";
        case Transponder::AdsbEmitterType::HighVortexLarge:
            return str << "High Vortex Large";
        case Transponder::AdsbEmitterType::Heavy:
            return str << "Heavy";
        case Transponder::AdsbEmitterType::HighlyManuv:
            return str << "Highly Manuv";
        case Transponder::AdsbEmitterType::Rotocraft:
            return str << "Rotocraft";
        case Transponder::AdsbEmitterType::Unassigned:
            return str << "Unassigned";
        case Transponder::AdsbEmitterType::Glider:
            return str << "Glider";
        case Transponder::AdsbEmitterType::LighterAir:
            return str << "Lighter Air";
        case Transponder::AdsbEmitterType::Parachute:
            return str << "Parachute";
        case Transponder::AdsbEmitterType::UltraLight:
            return str << "Ultra Light";
        case Transponder::AdsbEmitterType::Unassigned2:
            return str << "Unassigned2";
        case Transponder::AdsbEmitterType::Uav:
            return str << "Uav";
        case Transponder::AdsbEmitterType::Space:
            return str << "Space";
        case Transponder::AdsbEmitterType::Unassgined3:
            return str << "Unassgined3";
        case Transponder::AdsbEmitterType::EmergencySurface:
            return str << "Emergency Surface";
        case Transponder::AdsbEmitterType::ServiceSurface:
            return str << "Service Surface";
        case Transponder::AdsbEmitterType::PointObstacle:
            return str << "Point Obstacle";
        default:
            return str << "Unknown";
    }
}


} // namespace mavsdk