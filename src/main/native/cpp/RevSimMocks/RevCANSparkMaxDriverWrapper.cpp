

#include "RevSimMocks/RevCANSparkMaxDriverWrapper.h"

#include <vector>

#include "RevSimUtils/MockHooks.h"

#define RECEIVE_HELPER(paramName, size) \
    uint8_t buffer[size]; /* NOLINT */  \
    std::memset(&buffer[0], 0, size);   \
    Receive(paramName, buffer, size);   \
    uint32_t buffer_pos = 0;

std::vector<SnobotSim::REV_CallbackFunc> gCANSparkMaxDriverCallbacks;

void SnobotSim::SetCANSparkMaxDriverCallback(SnobotSim::REV_CallbackFunc callback)
{
    gCANSparkMaxDriverCallbacks.clear();
    gCANSparkMaxDriverCallbacks.push_back(callback);
}

SnobotSim::RevCANSparkMaxDriverWrapper::RevCANSparkMaxDriverWrapper(int aDeviceId) :
        mDeviceId(aDeviceId)
{
    Send("Create");
}
void SnobotSim::RevCANSparkMaxDriverWrapper::Receive(const std::string& aName, uint8_t* aBuffer, int aSize)
{
    if (!gCANSparkMaxDriverCallbacks.empty())
    {
        gCANSparkMaxDriverCallbacks[0](aName.c_str(), mDeviceId, aBuffer, aSize);
    }
    else
    {
        LOG_UNSUPPORTED_CAN_FUNC("Callback " << aName << " not registered");
    }
}

void SnobotSim::RevCANSparkMaxDriverWrapper::Send(const std::string& aName, uint8_t* aBuffer, int aSize)
{
    if (!gCANSparkMaxDriverCallbacks.empty())
    {
        gCANSparkMaxDriverCallbacks[0](aName.c_str(), mDeviceId, aBuffer, aSize);
    }
    else
    {
        LOG_UNSUPPORTED_CAN_FUNC("Callback " << aName << " not registered");
    }
}

///////////////////////////////////////////////////////////////////////////////////
void SnobotSim::RevCANSparkMaxDriverWrapper::GetFirmwareVersion(c_SparkMax_FirmwareVersion* fwVersion)
{
    RECEIVE_HELPER("GetFirmwareVersion", sizeof(*fwVersion));
    PoplateReceiveResults(buffer, fwVersion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSerialNumber(uint32_t* serialNumber[3])
{
    RECEIVE_HELPER("GetSerialNumber", sizeof(*serialNumber[3]));
    PoplateReceiveResults(buffer, serialNumber[3], buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetDeviceId(int* deviceId)
{
    RECEIVE_HELPER("GetDeviceId", sizeof(*deviceId));
    PoplateReceiveResults(buffer, deviceId, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetMotorType(c_SparkMax_MotorType type)
{
    Send("SetMotorType", type);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetMotorType(c_SparkMax_MotorType* type)
{
    RECEIVE_HELPER("GetMotorType", sizeof(*type));
    PoplateReceiveResults(buffer, type, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetPeriodicFramePeriod(c_SparkMax_PeriodicFrame frameId, int periodMs)
{
    Send("SetPeriodicFramePeriod", frameId, periodMs);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetControlFramePeriod(int periodMs)
{
    Send("SetControlFramePeriod", periodMs);
}
int SnobotSim::RevCANSparkMaxDriverWrapper::GetControlFramePeriod()
{
    int controlFramePeriod = 0;
    RECEIVE_HELPER("GetControlFramePeriod", sizeof(controlFramePeriod));
    PoplateReceiveResults(buffer, &controlFramePeriod, buffer_pos);
    return controlFramePeriod;
}
void SnobotSim::RevCANSparkMaxDriverWrapper::SetParameterFloat32(c_SparkMax_ConfigParameter paramId, float value)
{
    Send("SetParameterFloat32", paramId, value);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetParameterInt32(c_SparkMax_ConfigParameter paramId, int32_t value)
{
    Send("SetParameterInt32", paramId, value);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetParameterUint32(c_SparkMax_ConfigParameter paramId, uint32_t value)
{
    Send("SetParameterUint32", paramId, value);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetParameterBool(c_SparkMax_ConfigParameter paramId, uint8_t value)
{
    Send("SetParameterBool", paramId, value);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetParameterFloat32(c_SparkMax_ConfigParameter paramId, float* value)
{
    RECEIVE_HELPER("GetParameterFloat32", sizeof(paramId) + sizeof(*value));
    PoplateReceiveResults(buffer, &paramId, buffer_pos);
    PoplateReceiveResults(buffer, value, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetParameterInt32(c_SparkMax_ConfigParameter paramId, int32_t* value)
{
    RECEIVE_HELPER("GetParameterInt32", sizeof(paramId) + sizeof(*value));
    PoplateReceiveResults(buffer, &paramId, buffer_pos);
    PoplateReceiveResults(buffer, value, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetParameterUint32(c_SparkMax_ConfigParameter paramId, uint32_t* value)
{
    RECEIVE_HELPER("GetParameterUint32", sizeof(paramId) + sizeof(*value));
    PoplateReceiveResults(buffer, &paramId, buffer_pos);
    PoplateReceiveResults(buffer, value, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetParameterBool(c_SparkMax_ConfigParameter paramId, uint8_t* value)
{
    RECEIVE_HELPER("GetParameterBool", sizeof(paramId) + sizeof(*value));
    PoplateReceiveResults(buffer, &paramId, buffer_pos);
    PoplateReceiveResults(buffer, value, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPeriodicStatus0(c_SparkMax_PeriodicStatus0* rawframe)
{
    RECEIVE_HELPER("GetPeriodicStatus0", sizeof(*rawframe));
    PoplateReceiveResults(buffer, rawframe, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPeriodicStatus1(c_SparkMax_PeriodicStatus1* rawframe)
{
    RECEIVE_HELPER("GetPeriodicStatus1", sizeof(*rawframe));
    PoplateReceiveResults(buffer, rawframe, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPeriodicStatus2(c_SparkMax_PeriodicStatus2* rawframe)
{
    RECEIVE_HELPER("GetPeriodicStatus2", sizeof(*rawframe));
    PoplateReceiveResults(buffer, rawframe, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPeriodicStatus3(c_SparkMax_PeriodicStatus3* rawframe)
{
    RECEIVE_HELPER("GetPeriodicStatus3", sizeof(*rawframe));
    PoplateReceiveResults(buffer, rawframe, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPeriodicStatus4(c_SparkMax_PeriodicStatus4* rawframe)
{
    RECEIVE_HELPER("GetPeriodicStatus4", sizeof(*rawframe));
    PoplateReceiveResults(buffer, rawframe, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetEncoderPosition(float position)
{
    Send("SetEncoderPosition", position);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderPosition(float position)
{
    Send("SetAltEncoderPosition", position);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::RestoreFactoryDefaults(uint8_t persist)
{
    Send("RestoreFactoryDefaults", persist);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::FactoryWipe(uint8_t persist)
{
    Send("FactoryWipe", persist);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetFollow(uint32_t followerArbId, uint32_t followerCfg)
{
    Send("SetFollow", followerArbId, followerCfg);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetpointCommand(float value, c_SparkMax_ControlType ctrl, int pidSlot, float arbFeedforward, int arbFFUnits)
{
    Send("SetpointCommand", value, ctrl, pidSlot, arbFeedforward, arbFFUnits);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetDRVStatus(c_SparkMax_DRVStatus* drvStatus)
{
    RECEIVE_HELPER("GetDRVStatus", sizeof(*drvStatus));
    PoplateReceiveResults(buffer, drvStatus, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetInverted(uint8_t inverted)
{
    Send("SetInverted", inverted);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetInverted(uint8_t* inverted)
{
    RECEIVE_HELPER("GetInverted", sizeof(*inverted));
    PoplateReceiveResults(buffer, inverted, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartCurrentLimit(uint8_t stallLimit, uint8_t freeLimit, uint32_t limitRPM)
{
    Send("SetSmartCurrentLimit", stallLimit, freeLimit, limitRPM);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartCurrentLimit(uint8_t* stallLimit, uint8_t* freeLimit, uint32_t* limitRPM)
{
    RECEIVE_HELPER("GetSmartCurrentLimit", sizeof(*stallLimit) + sizeof(*freeLimit) + sizeof(*limitRPM));
    PoplateReceiveResults(buffer, stallLimit, buffer_pos);
    PoplateReceiveResults(buffer, freeLimit, buffer_pos);
    PoplateReceiveResults(buffer, limitRPM, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSecondaryCurrentLimit(float limit, int chopCycles)
{
    Send("SetSecondaryCurrentLimit", limit, chopCycles);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSecondaryCurrentLimit(float* limit, int* chopCycles)
{
    RECEIVE_HELPER("GetSecondaryCurrentLimit", sizeof(*limit) + sizeof(*chopCycles));
    PoplateReceiveResults(buffer, limit, buffer_pos);
    PoplateReceiveResults(buffer, chopCycles, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetIdleMode(c_SparkMax_IdleMode idlemode)
{
    Send("SetIdleMode", idlemode);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetIdleMode(c_SparkMax_IdleMode* idlemode)
{
    RECEIVE_HELPER("GetIdleMode", sizeof(*idlemode));
    PoplateReceiveResults(buffer, idlemode, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::EnableVoltageCompensation(float nominalVoltage)
{
    Send("EnableVoltageCompensation", nominalVoltage);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetVoltageCompensationNominalVoltage(float* nominalVoltage)
{
    RECEIVE_HELPER("GetVoltageCompensationNominalVoltage", sizeof(*nominalVoltage));
    PoplateReceiveResults(buffer, nominalVoltage, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::DisableVoltageCompensation()
{
    Send("DisableVoltageCompensation");
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetOpenLoopRampRate(float rate)
{
    Send("SetOpenLoopRampRate", rate);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetOpenLoopRampRate(float* rate)
{
    RECEIVE_HELPER("GetOpenLoopRampRate", sizeof(*rate));
    PoplateReceiveResults(buffer, rate, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetClosedLoopRampRate(float rate)
{
    Send("SetClosedLoopRampRate", rate);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetClosedLoopRampRate(float* rate)
{
    RECEIVE_HELPER("GetClosedLoopRampRate", sizeof(*rate));
    PoplateReceiveResults(buffer, rate, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::IsFollower(uint8_t* isFollower)
{
    RECEIVE_HELPER("IsFollower", sizeof(*isFollower));
    PoplateReceiveResults(buffer, isFollower, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetFaults(uint16_t* faults)
{
    RECEIVE_HELPER("GetFaults", sizeof(*faults));
    PoplateReceiveResults(buffer, faults, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetStickyFaults(uint16_t* stickyFaults)
{
    RECEIVE_HELPER("GetStickyFaults", sizeof(*stickyFaults));
    PoplateReceiveResults(buffer, stickyFaults, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetFault(c_SparkMax_FaultID faultId, uint8_t* fault)
{
    RECEIVE_HELPER("GetFault", sizeof(faultId) + sizeof(*fault));
    PoplateReceiveResults(buffer, &faultId, buffer_pos);
    PoplateReceiveResults(buffer, fault, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetStickyFault(c_SparkMax_FaultID faultId, uint8_t* stickyfault)
{
    RECEIVE_HELPER("GetStickyFault", sizeof(faultId) + sizeof(*stickyfault));
    PoplateReceiveResults(buffer, &faultId, buffer_pos);
    PoplateReceiveResults(buffer, stickyfault, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetBusVoltage(float* busVoltage)
{
    RECEIVE_HELPER("GetBusVoltage", sizeof(*busVoltage));
    PoplateReceiveResults(buffer, busVoltage, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAppliedOutput(float* appliedOutput)
{
    RECEIVE_HELPER("GetAppliedOutput", sizeof(*appliedOutput));
    PoplateReceiveResults(buffer, appliedOutput, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetOutputCurrent(float* outputCurrent)
{
    RECEIVE_HELPER("GetOutputCurrent", sizeof(*outputCurrent));
    PoplateReceiveResults(buffer, outputCurrent, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetMotorTemperature(float* motorTemperature)
{
    RECEIVE_HELPER("GetMotorTemperature", sizeof(*motorTemperature));
    PoplateReceiveResults(buffer, motorTemperature, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::ClearFaults()
{
    Send("ClearFaults");
}

void SnobotSim::RevCANSparkMaxDriverWrapper::BurnFlash()
{
    Send("BurnFlash");
}
void SnobotSim::RevCANSparkMaxDriverWrapper::SetCANTimeout(int timeoutMs)
{
    Send("SetCANTimeout", timeoutMs);
}
void SnobotSim::RevCANSparkMaxDriverWrapper::EnableSoftLimit(c_SparkMax_LimitDirection dir, uint8_t enable)
{
    Send("EnableSoftLimit", dir, enable);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::IsSoftLimitEnabled(c_SparkMax_LimitDirection dir, uint8_t* enabled)
{
    RECEIVE_HELPER("IsSoftLimitEnabled", sizeof(dir) + sizeof(*enabled));
    PoplateReceiveResults(buffer, &dir, buffer_pos);
    PoplateReceiveResults(buffer, enabled, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSoftLimit(c_SparkMax_LimitDirection dir, float limit)
{
    Send("SetSoftLimit", dir, limit);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSoftLimit(c_SparkMax_LimitDirection dir, float* limit)
{
    RECEIVE_HELPER("GetSoftLimit", sizeof(dir) + sizeof(*limit));
    PoplateReceiveResults(buffer, &dir, buffer_pos);
    PoplateReceiveResults(buffer, limit, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSensorType(c_SparkMax_EncoderType sensorType)
{
    Send("SetSensorType", sensorType);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::Identify()
{
    Send("Identify");
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetLimitPolarity(c_SparkMax_LimitDirection sw, c_SparkMax_LimitPolarity polarity)
{
    Send("SetLimitPolarity", sw, polarity);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetLimitPolarity(c_SparkMax_LimitDirection sw, c_SparkMax_LimitPolarity* polarity)
{
    RECEIVE_HELPER("GetLimitPolarity", sizeof(sw) + sizeof(*polarity));
    PoplateReceiveResults(buffer, &sw, buffer_pos);
    PoplateReceiveResults(buffer, polarity, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetLimitSwitch(c_SparkMax_LimitDirection sw, uint8_t* limit)
{
    RECEIVE_HELPER("GetLimitSwitch", sizeof(sw) + sizeof(*limit));
    PoplateReceiveResults(buffer, &sw, buffer_pos);
    PoplateReceiveResults(buffer, limit, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::EnableLimitSwitch(c_SparkMax_LimitDirection sw, uint8_t enable)
{
    Send("EnableLimitSwitch", sw, enable);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::IsLimitEnabled(c_SparkMax_LimitDirection sw, uint8_t* enabled)
{
    RECEIVE_HELPER("IsLimitEnabled", sizeof(sw) + sizeof(*enabled));
    PoplateReceiveResults(buffer, &sw, buffer_pos);
    PoplateReceiveResults(buffer, enabled, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogPosition(float* position)
{
    RECEIVE_HELPER("GetAnalogPosition", sizeof(*position));
    PoplateReceiveResults(buffer, position, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogVelocity(float* velocity)
{
    RECEIVE_HELPER("GetAnalogVelocity", sizeof(*velocity));
    PoplateReceiveResults(buffer, velocity, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogVoltage(float* voltage)
{
    RECEIVE_HELPER("GetAnalogVoltage", sizeof(*voltage));
    PoplateReceiveResults(buffer, voltage, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogPositionConversionFactor(float conversion)
{
    Send("SetAnalogPositionConversionFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogVelocityConversionFactor(float conversion)
{
    Send("SetAnalogVelocityConversionFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogPositionConversionFactor(float* conversion)
{
    RECEIVE_HELPER("GetAnalogPositionConversionFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogVelocityConversionFactor(float* conversion)
{
    RECEIVE_HELPER("GetAnalogVelocityConversionFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogInverted(uint8_t inverted)
{
    Send("SetAnalogInverted", inverted);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogInverted(uint8_t* inverted)
{
    RECEIVE_HELPER("GetAnalogInverted", sizeof(*inverted));
    PoplateReceiveResults(buffer, inverted, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogAverageDepth(uint32_t depth)
{
    Send("SetAnalogAverageDepth", depth);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogAverageDepth(uint32_t* depth)
{
    RECEIVE_HELPER("GetAnalogAverageDepth", sizeof(*depth));
    PoplateReceiveResults(buffer, depth, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogMeasurementPeriod(uint32_t samples)
{
    Send("SetAnalogMeasurementPeriod", samples);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogMeasurementPeriod(uint32_t* samples)
{
    RECEIVE_HELPER("GetAnalogMeasurementPeriod", sizeof(*samples));
    PoplateReceiveResults(buffer, samples, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAnalogMode(c_SparkMax_AnalogMode mode)
{
    Send("SetAnalogMode", mode);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAnalogMode(c_SparkMax_AnalogMode* mode)
{
    RECEIVE_HELPER("GetAnalogMode", sizeof(*mode));
    PoplateReceiveResults(buffer, mode, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetEncoderPosition(float* position)
{
    RECEIVE_HELPER("GetEncoderPosition", sizeof(*position));
    PoplateReceiveResults(buffer, position, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetEncoderVelocity(float* velocity)
{
    RECEIVE_HELPER("GetEncoderVelocity", sizeof(*velocity));
    PoplateReceiveResults(buffer, velocity, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetPositionConversionFactor(float conversion)
{
    Send("SetPositionConversionFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetVelocityConversionFactor(float conversion)
{
    Send("SetVelocityConversionFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetPositionConversionFactor(float* conversion)
{
    RECEIVE_HELPER("GetPositionConversionFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetVelocityConversionFactor(float* conversion)
{
    RECEIVE_HELPER("GetVelocityConversionFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAverageDepth(uint32_t depth)
{
    Send("SetAverageDepth", depth);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAverageDepth(uint32_t* depth)
{
    RECEIVE_HELPER("GetAverageDepth", sizeof(*depth));
    PoplateReceiveResults(buffer, depth, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetMeasurementPeriod(uint32_t samples)
{
    Send("SetMeasurementPeriod", samples);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetMeasurementPeriod(uint32_t* samples)
{
    RECEIVE_HELPER("GetMeasurementPeriod", sizeof(*samples));
    PoplateReceiveResults(buffer, samples, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetCountsPerRevolution(uint32_t cpr)
{
    Send("SetCountsPerRevolution", cpr);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetCountsPerRevolution(uint32_t* cpr)
{
    RECEIVE_HELPER("GetCountsPerRevolution", sizeof(*cpr));
    PoplateReceiveResults(buffer, cpr, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetEncoderInverted(uint8_t inverted)
{
    Send("SetEncoderInverted", inverted);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetEncoderInverted(uint8_t* inverted)
{
    RECEIVE_HELPER("GetEncoderInverted", sizeof(*inverted));
    PoplateReceiveResults(buffer, inverted, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderPosition(float* position)
{
    RECEIVE_HELPER("GetAltEncoderPosition", sizeof(*position));
    PoplateReceiveResults(buffer, position, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderVelocity(float* velocity)
{
    RECEIVE_HELPER("GetAltEncoderVelocity", sizeof(*velocity));
    PoplateReceiveResults(buffer, velocity, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderPositionFactor(float conversion)
{
    Send("SetAltEncoderPositionFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderVelocityFactor(float conversion)
{
    Send("SetAltEncoderVelocityFactor", conversion);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderPositionFactor(float* conversion)
{
    RECEIVE_HELPER("GetAltEncoderPositionFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderVelocityFactor(float* conversion)
{
    RECEIVE_HELPER("GetAltEncoderVelocityFactor", sizeof(*conversion));
    PoplateReceiveResults(buffer, conversion, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderAverageDepth(uint32_t depth)
{
    Send("SetAltEncoderAverageDepth", depth);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderAverageDepth(uint32_t* depth)
{
    RECEIVE_HELPER("GetAltEncoderAverageDepth", sizeof(*depth));
    PoplateReceiveResults(buffer, depth, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderMeasurementPeriod(uint32_t samples)
{
    Send("SetAltEncoderMeasurementPeriod", samples);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderMeasurementPeriod(uint32_t* samples)
{
    RECEIVE_HELPER("GetAltEncoderMeasurementPeriod", sizeof(*samples));
    PoplateReceiveResults(buffer, samples, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderCountsPerRevolution(uint32_t cpr)
{
    Send("SetAltEncoderCountsPerRevolution", cpr);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderCountsPerRevolution(uint32_t* cpr)
{
    RECEIVE_HELPER("GetAltEncoderCountsPerRevolution", sizeof(*cpr));
    PoplateReceiveResults(buffer, cpr, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetAltEncoderInverted(uint8_t inverted)
{
    Send("SetAltEncoderInverted", inverted);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetAltEncoderInverted(uint8_t* inverted)
{
    RECEIVE_HELPER("GetAltEncoderInverted", sizeof(*inverted));
    PoplateReceiveResults(buffer, inverted, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetDataPortConfig(c_SparkMax_DataPortConfig config)
{
    Send("SetDataPortConfig", config);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetDataPortConfig(c_SparkMax_DataPortConfig* config)
{
    RECEIVE_HELPER("GetDataPortConfig", sizeof(*config));
    PoplateReceiveResults(buffer, config, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetP(int slotID, float gain)
{
    Send("SetP", slotID, gain);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetI(int slotID, float gain)
{
    Send("SetI", slotID, gain);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetD(int slotID, float gain)
{
    Send("SetD", slotID, gain);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetDFilter(int slotID, float gain)
{
    Send("SetDFilter", slotID, gain);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetFF(int slotID, float gain)
{
    Send("SetFF", slotID, gain);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetIZone(int slotID, float IZone)
{
    Send("SetIZone", slotID, IZone);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetOutputRange(int slotID, float min, float max)
{
    Send("SetOutputRange", slotID, min, max);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetP(int slotID, float* gain)
{
    RECEIVE_HELPER("GetP", sizeof(slotID) + sizeof(*gain));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, gain, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetI(int slotID, float* gain)
{
    RECEIVE_HELPER("GetI", sizeof(slotID) + sizeof(*gain));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, gain, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetD(int slotID, float* gain)
{
    RECEIVE_HELPER("GetD", sizeof(slotID) + sizeof(*gain));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, gain, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetDFilter(int slotID, float* gain)
{
    RECEIVE_HELPER("GetDFilter", sizeof(slotID) + sizeof(*gain));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, gain, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetFF(int slotID, float* gain)
{
    RECEIVE_HELPER("GetFF", sizeof(slotID) + sizeof(*gain));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, gain, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetIZone(int slotID, float* IZone)
{
    RECEIVE_HELPER("GetIZone", sizeof(slotID) + sizeof(*IZone));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, IZone, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetOutputMin(int slotID, float* min)
{
    RECEIVE_HELPER("GetOutputMin", sizeof(slotID) + sizeof(*min));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, min, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetOutputMax(int slotID, float* max)
{
    RECEIVE_HELPER("GetOutputMax", sizeof(slotID) + sizeof(*max));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, max, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartMotionMaxVelocity(int slotID, float maxVel)
{
    Send("SetSmartMotionMaxVelocity", slotID, maxVel);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartMotionMaxAccel(int slotID, float maxAccel)
{
    Send("SetSmartMotionMaxAccel", slotID, maxAccel);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartMotionMinOutputVelocity(int slotID, float minVel)
{
    Send("SetSmartMotionMinOutputVelocity", slotID, minVel);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartMotionAccelStrategy(int slotID, c_SparkMax_AccelStrategy accelStrategy)
{
    Send("SetSmartMotionAccelStrategy", slotID, accelStrategy);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetSmartMotionAllowedClosedLoopError(int slotID, float allowedError)
{
    Send("SetSmartMotionAllowedClosedLoopError", slotID, allowedError);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartMotionMaxVelocity(int slotID, float* maxVel)
{
    RECEIVE_HELPER("GetSmartMotionMaxVelocity", sizeof(slotID) + sizeof(*maxVel));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, maxVel, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartMotionMaxAccel(int slotID, float* maxAccel)
{
    RECEIVE_HELPER("GetSmartMotionMaxAccel", sizeof(slotID) + sizeof(*maxAccel));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, maxAccel, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartMotionMinOutputVelocity(int slotID, float* minVel)
{
    RECEIVE_HELPER("GetSmartMotionMinOutputVelocity", sizeof(slotID) + sizeof(*minVel));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, minVel, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartMotionAccelStrategy(int slotID, c_SparkMax_AccelStrategy* accelStrategy)
{
    RECEIVE_HELPER("GetSmartMotionAccelStrategy", sizeof(slotID) + sizeof(*accelStrategy));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, accelStrategy, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetSmartMotionAllowedClosedLoopError(int slotID, float* allowedError)
{
    RECEIVE_HELPER("GetSmartMotionAllowedClosedLoopError", sizeof(slotID) + sizeof(*allowedError));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, allowedError, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetIMaxAccum(int slotID, float iMaxAccum)
{
    Send("SetIMaxAccum", slotID, iMaxAccum);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetIMaxAccum(int slotID, float* iMaxAccum)
{
    RECEIVE_HELPER("GetIMaxAccum", sizeof(slotID) + sizeof(*iMaxAccum));
    PoplateReceiveResults(buffer, &slotID, buffer_pos);
    PoplateReceiveResults(buffer, iMaxAccum, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetIAccum(float iAccum)
{
    Send("SetIAccum", iAccum);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetIAccum(float* iAccum)
{
    RECEIVE_HELPER("GetIAccum", sizeof(*iAccum));
    PoplateReceiveResults(buffer, iAccum, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetFeedbackDevice(uint32_t sensorID)
{
    Send("SetFeedbackDevice", sensorID);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetFeedbackDeviceID(uint32_t* id)
{
    RECEIVE_HELPER("GetFeedbackDeviceID", sizeof(*id));
    PoplateReceiveResults(buffer, id, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetFeedbackDeviceRange(float min, float max)
{
    Send("SetFeedbackDeviceRange", min, max);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::SetLastError(c_SparkMax_ErrorCode error)
{
    Send("SetLastError", error);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::GetLastError()
{
    Send("GetLastError");
}

void SnobotSim::RevCANSparkMaxDriverWrapper::ReadTelemetryStream(uint32_t telemetryHandle, c_SparkMax_TelemetryMessage* messages, c_SparkMax_TelemetryID* ids, uint32_t numOfStreams)
{
    RECEIVE_HELPER("ReadTelemetryStream", sizeof(telemetryHandle) + sizeof(*messages) + sizeof(*ids) + sizeof(numOfStreams));
    PoplateReceiveResults(buffer, &telemetryHandle, buffer_pos);
    PoplateReceiveResults(buffer, messages, buffer_pos);
    PoplateReceiveResults(buffer, ids, buffer_pos);
    PoplateReceiveResults(buffer, &numOfStreams, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::OpenTelemetryStream(uint32_t* telemetryHandle)
{
    RECEIVE_HELPER("OpenTelemetryStream", sizeof(*telemetryHandle));
    PoplateReceiveResults(buffer, telemetryHandle, buffer_pos);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::CloseTelemetryStream(uint32_t telemetryHandle)
{
    Send("CloseTelemetryStream", telemetryHandle);
}

void SnobotSim::RevCANSparkMaxDriverWrapper::ListTelemetryStream(c_SparkMax_TelemetryMessage* messages)
{
    RECEIVE_HELPER("ListTelemetryStream", sizeof(*messages));
    PoplateReceiveResults(buffer, messages, buffer_pos);
}