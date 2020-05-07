#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define  Max_count  512
#define  MIN(x,y)  (((x) <= (y)) ? (x) : (y))   //find minimum
#define  BULK_IN  0x02
#define  BULK_OUT  0x81

static struct usb_device *usb_dev;
static struct usb_class_driver usb_class;
static unsigned char data[Max_count]; 

static int sample_open(struct inode *inode, struct file *file)
{
	return 0;
}
static int sample_close(struct inode *inode, struct file *file)
{
	return 0;
}
static ssize_t sample_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	int ret,ret2;
	int read_count;
	
	ret = usb_bulk_msg(usb_dev, usb_rcvbulkpipe(usb_dev, BULK_IN), data, Max_count, &read_count, 10000);
	if(ret)
	{
		printk("Bulk message returned:%d\n", ret);
		return ret;
	}
	ret2 = copy_to_user(buf, data, MIN(count, read_count));
	if(ret2)
	{
		return -EINVAL;
	}
	return MIN(count, read_count);
}
static ssize_t sample_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	int ret,ret2;
	int write_count;
	write_count = MIN(count, Max_count);
	
	ret2 = copy_to_user(data, buf, MIN(count, Max_count));
	if(ret2)
	{
		return -EINVAL;
	}
	ret = usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, BULK_OUT), data, MIN(count, Max_count), &write_count, 10000);
	if(ret)
	{
		printk("Bulk message returned:%d\n", ret);
		return ret;
	}
	return write_count;
}

static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = sample_open,
	.release = sample_close,
	.read = sample_read,
	.write = sample_write,
};
	
	
static int sample_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	int ret;
	usb_dev = interface_to_usbdev(interface);
	usb_class.name = "usb%d";
	usb_class.fops = &fops;
	ret = usb_register_dev(interface, &usb_class);
	if(ret)
	{
		printk("Minor number not allocated\n");
	}
	printk("Sample Pen-drive (%04X:%04X) plugged in\n", id->idVendor, id->idProduct);
	return ret;
}
static void sample_disconnect(struct usb_interface *interface)
{
	usb_deregister_dev(interface, &usb_class);
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
	
module_init(sample_init);
module_exit(sample_exit);

MODULE_LICENSE("GPL");
