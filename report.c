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

int usb_bulk_msg(struct usb_device *usb_dev, unsigned int pipe, void *data, int len, int *actual_length, int timeout);

int ret;
ret = usb_submit_urb(urb, GFP_KERNEL);
if(ret)
{
	printk(“urb submission unsuccessful\n”);
}

usb_fill_bulk_urb(urb,dev->udev,usb_sndbulkpipe(dev->udev,dev->bulk_out_endpointAddr), buf, count, write_bulk_callback, dev);

copy_from_user(Buffer, user_buffer, count);

Buffer = usb_buffer_alloc(dev->udev, count, GFP_KERNEL, &urb->transfer_dma);

urb = usb_alloc_urb(0, GFP_KERNEL);

int ret;
ret = usb_register_dev(interface, &usb_class);
if(ret)
{
	printk(“minor number not allocated\n”);
	usb_set_interface(interface, NULL);
}

static inline void usb_set_intfdata(struct usb_interface *intf, void *data);

static void __exit sample_usb_exit(void)
{
            usb_deregister(&sample_driver);
}

static int __init sample_usb_init(void)
{
	int ret;
	ret = usb_register(&sample_driver);
	if(ret)
	{
		printk(“usb_register unsuccessful, error number is:%d”,ret);
	}
	return ret;
}


static struct usb_driver sample_driver = {
	.owner          = THIS_MODULE,
	.name           = sample,
	.id_table       = sample_id_table
	.probe          = sample_probe,
	.disconnect	= sample_disconnect,
};

const struct usb_device_id *id_table;

static struct usb_device_id sample_id_table [] = {
	{ USB_DEVICE(vendor_id, product_id) },
	{ }
};
MODULE_DEVICE_TABLE(usb, id_table);

void (*usb_complete_t) (
	struct urb*,
	struct pt_regs*
);



module_init(sample_init);
module_exit(sample_exit);

MODULE_LICENSE("GPL");
