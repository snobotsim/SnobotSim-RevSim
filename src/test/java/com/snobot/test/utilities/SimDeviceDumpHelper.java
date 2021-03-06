package com.snobot.test.utilities;

import java.lang.reflect.Field;

import edu.wpi.first.hal.sim.SimDeviceSim;
import edu.wpi.first.hal.sim.mockdata.SimDeviceDataJNI.SimDeviceInfo;
import edu.wpi.first.hal.sim.mockdata.SimDeviceDataJNI.SimValueInfo;

public final class SimDeviceDumpHelper
{
    private SimDeviceDumpHelper()
    {
        // Nothing to do
    }

    private static String getName(Class<?> aClazz, Object aDeviceName)
    {
        try
        {
            Field privateStringField = aClazz.getDeclaredField("name");

            privateStringField.setAccessible(true);

            String name = (String) privateStringField.get(aDeviceName);
            return name;
        }
        catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException ex)
        {
            ex.printStackTrace(); // NOPMD
            throw new RuntimeException(ex); // NOPMD
        }
    }

    @SuppressWarnings("PMD.ConsecutiveLiteralAppends")
    public static void dumpSimDevices()
    {
        StringBuilder builder = new StringBuilder(200);
        builder.append("***************************************************\nDumping devices:\n");
        for (SimDeviceInfo deviceSimName : SimDeviceSim.enumerateDevices(""))
        {
            builder.append("Got a device: \n");

            String deviceName = getName(SimDeviceInfo.class, deviceSimName);
            builder.append("  ").append(deviceName).append('\n');

            SimDeviceSim simDeviceSime = new SimDeviceSim(deviceName); // NOPMD
            for (SimValueInfo valueName : simDeviceSime.enumerateValues())
            {
                String sim = getName(SimValueInfo.class, valueName);
                builder.append("    ").append(sim).append('\n');
            }
        }
        builder.append("***************************************************\n");
        System.out.println(builder); // NOPMD

    }
}
