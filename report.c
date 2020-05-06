#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
static int sample_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk("Sample Pen-drive (%04X:%04X) plugged in\n", id->idVendor, id->idProduct);
	return 0;
}
static void sample_disconnect(struct usb_interface *interface)
{
	printk("Sample Pen-drive removed\n");
}
static struct usb_device_id sample_table[] =
{
	{USB_DEVICE(0x0781, 0x5577)},
	{}
};
MODULE_DEVICE_TABLE(usb, sample_table);
static struct usb_driver sample_driver = 
{
	 .name         = "sample driver",
	 .id_table     = sample_table,
	 .probe	       = sample_probe,
	 .disconnect   = sample_disconnect,
};
static int __init sample_init(void)
{
	int ret;
	ret = usb_register(&sample_driver);
	if(ret)
	{
		printk("Driver registration unsuccessful\n");
	}
	return ret;
}
static void __exit sample_exit(void)
{
	usb_deregister(&sample_driver);
}

int usb_control_msg(struct usb_device *dev, unsigned int pipe, __u8 request, __u8 requesttype, __u16 value, __u16 index, void *data, __u16 size, int timeout);

module_init(sample_init);
module_exit(sample_exit);

MODULE_LICENSE("GPL");
