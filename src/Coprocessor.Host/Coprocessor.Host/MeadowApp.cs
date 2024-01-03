using Meadow;
using Meadow.Devices;
using System.Text;
using System.Threading.Tasks;

namespace Coprocessor.Host;

public class MeadowApp : App<F7FeatherV2>
{
    public override async Task Run()
    {
        var bus = Device.CreateI2cBus();

        var tx_buffer = new byte[1];
        var rx_buffer = new byte[4];
        var i = 0;
        byte bus_address = 0x42;

        while (true)
        {
            tx_buffer[0] = i switch
            {
                0 => 0,
                1 => 1,
                2 => 2,
                _ => 3
            };

            Resolver.Log.Info($"Writing {i}");
            bus.Write(bus_address, tx_buffer);

            bus.Read(bus_address, rx_buffer);
            Resolver.Log.Info($"Read back {Encoding.ASCII.GetString(rx_buffer)}");

            await Task.Delay(2000);
            if (++i > 3) i = 0;
        }
    }
}