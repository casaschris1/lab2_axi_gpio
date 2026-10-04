#include "xparameters.h"
#include "xgpio.h"
#include "xil_printf.h"
#include "xstatus.h"

#define LED_DEVICE_ID      XPAR_AXI_GPIO_0_DEVICE_ID
#define RGB_DEVICE_ID      XPAR_AXI_GPIO_1_DEVICE_ID
#define SWITCH_DEVICE_ID   XPAR_AXI_GPIO_2_DEVICE_ID

XGpio LedGpio;
XGpio RgbGpio;
XGpio SwitchGpio;

int main ()
{
	int status;
	u32 switch_value;
	u32 binary_count = 0;
	u32 ring_count = 0x1;
	status = XGpio_Initialize(&LedGpio, LED_DEVICE_ID);
			if (status != XST_SUCCESS)
				return XST_FAILURE;
	status = XGpio_Initialize(&RgbGpio, RGB_DEVICE_ID);
			if (status != XST_SUCCESS)
				return XST_FAILURE;
	status = XGpio_Initialize(&SwitchGpio, SWITCH_DEVICE_ID);
			if (status != XST_SUCCESS)
				return XST_FAILURE;
// LEDs are outputs
			XGpio_SetDataDirection(&LedGpio, 1, 0x0);
// RGB LED is an output
XGpio_SetDataDirection(&RgbGpio, 1, 0x0);
// Switches are the inputs
XGpio_SetDataDirection(&SwitchGpio, 1, 0xF);
xil_printf("AXI GPIO initialized successfully!\r\n");

// reads four switches, mirrors them onto the four LEDs
while (1)
{
	switch_value = XGpio_DiscreteRead(&SwitchGpio, 1);
	switch (switch_value)
	{
	case 0x1: // Switch 0
		XGpio_DiscreteWrite(&LedGpio, 1, 0x1);
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x1); // Red
		break;
	case 0x2: // Switch 1
		XGpio_DiscreteWrite(&LedGpio, 1, 0x2);
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x2); // Green
		break;
	case 0x4: // Switch 2
		XGpio_DiscreteWrite(&LedGpio, 1, 0x4);
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x4);
		break;
	case 0x8: // Switch 3
		XGpio_DiscreteWrite(&LedGpio, 1, 0x8);
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x7);
		break;
	case 0x3: // Switch 0 + 1
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x0); // RGB off
		XGpio_DiscreteWrite(&LedGpio, 1, binary_count);

		binary_count++;
		if (binary_count > 0xF)
			binary_count = 0x0;
		for (volatile int delay = 0; delay < 1000000; delay++);
		break;
	case 0xC: // Switch 2 + 3
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x0); // RGB off
		XGpio_DiscreteWrite(&LedGpio, 1, ring_count);

		ring_count = ring_count << 1;
		if (ring_count > 0x8)
			ring_count = 0x1;
		for (volatile int delay = 0; delay < 10000000; delay++);
		break;
	default:
		XGpio_DiscreteWrite(&LedGpio, 1, 0x0);
		XGpio_DiscreteWrite(&RgbGpio, 1, 0x0);
		binary_count = 0x0;
		ring_count = 0x1;
		break;
	}
}
return 0;

}

