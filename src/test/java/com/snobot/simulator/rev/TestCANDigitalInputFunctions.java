package com.snobot.simulator.rev;

import java.nio.ByteBuffer;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import com.revrobotics.CANDigitalInput;
import com.revrobotics.CANDigitalInput.LimitSwitchPolarity;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;
import com.snobot.test.utilities.SimDeviceDumpHelper;

import edu.wpi.first.hal.HAL;
import edu.wpi.first.hal.sim.SimDeviceSim;
import edu.wpi.first.hal.sim.mockdata.SimulatorJNI;

public class TestCANDigitalInputFunctions
{
    private final RevCallback mRevCallback = new RevCallback()
    {
        @Override
        public void callback(String aName, int aDeviceId, ByteBuffer aBuffer, int aCount)
        {
            System.out.println("Getting CANDigital callback '" + aName + "' with size of " + aBuffer.capacity() + ", " + aCount); // NOPMD
        }
    };

    @BeforeEach
    public void initialize()
    {
        HAL.initialize(0, 0);
        System.loadLibrary("SparkMaxDriver");

        SimulatorJNI.resetHandles();
        SimDeviceSim.resetData();
        RevSimJni.registerRevCallback(mRevCallback);

    }

    @Test
    public void testLimitSwitchFunctions()
    {
        CANSparkMax sc = new CANSparkMax(11, MotorType.kBrushless);
        SimDeviceDumpHelper.dumpSimDevices();

        for (LimitSwitchPolarity polarity : LimitSwitchPolarity.values())
        {
            CANDigitalInput reverseSwitch = sc.getReverseLimitSwitch(polarity);
            CANDigitalInput fowrardSwitch = sc.getForwardLimitSwitch(polarity);

            reverseSwitch.enableLimitSwitch(false);
            reverseSwitch.enableLimitSwitch(true);
            reverseSwitch.get();
            reverseSwitch.isLimitSwitchEnabled();

            fowrardSwitch.enableLimitSwitch(false);
            fowrardSwitch.enableLimitSwitch(true);
            fowrardSwitch.get();
            fowrardSwitch.isLimitSwitchEnabled();
        }
    }
}
