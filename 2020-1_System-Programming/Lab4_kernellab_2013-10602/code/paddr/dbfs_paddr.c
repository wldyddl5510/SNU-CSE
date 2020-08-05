#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>

#define OFFSET_MASK 0x0000000000000fff
#define ADDR_MASK	0x0000fffffffff000

MODULE_LICENSE("GPL");

static struct dentry *dir, *output;
static struct task_struct *task;

struct packet {
	pid_t pid;
	unsigned long vaddr;
	unsigned long paddr;
};

static ssize_t read_output(struct file *fp,
                        char __user *user_buffer,
                        size_t length,
                        loff_t *position)
{
	// Implement read file operation
	struct packet pckt;
	// page table walk -> 5 level page table
	pgd_t *l5_entry;
	// after kernel 4.11, there is p4d
	p4d_t *l4_entry;
	pud_t *l3_entry;
	pmd_t *l2_entry;
	pte_t *l1_entry;

	// addr and offset -> will concat later
	unsigned long physical_addr = 0;
	unsigned long physical_offset = 0;

	copy_from_user(&pckt, user_buffer, sizeof(struct packet));
	
	task = pid_task(find_vpid(pckt.pid), PIDTYPE_PID);

	// inside task, there is a mm_strcut *mm, which contain info of page table
	l5_entry = pgd_offset(task->mm, pckt.vaddr);
	l4_entry = p4d_offset(l5_entry, pckt.vaddr);
	l3_entry = pud_offset(l4_entry, pckt.vaddr);
	l2_entry = pmd_offset(l3_entry, pckt.vaddr);
	l1_entry = pte_offset_kernel(l2_entry, pckt.vaddr);

	// get page offset and addr
	physical_addr = pte_val(*l1_entry) & ADDR_MASK;
	physical_offset = pckt.vaddr & OFFSET_MASK;
	
	// concat
	pckt.paddr = physical_addr | physical_offset;

	printk("physical address: %lx\n", pckt.paddr);
	pte_unmap(l1_entry);

	// back to user
	copy_to_user(user_buffer, &pckt, sizeof(struct packet));

	return length;
}

static const struct file_operations dbfs_fops = {
        // Mapping file operations with your functions
	.read = read_output
};

static int __init dbfs_module_init(void)
{

	printk("dbfs_paddr module initialize done\n");
        // Implement init module

//#if 0
        dir = debugfs_create_dir("paddr", NULL);

        if (!dir) {
                printk("Cannot create paddr dir\n");
                return -1;
        }

        // Fill in the arguments below
        output = debugfs_create_file("output", 0444, dir, NULL, &dbfs_fops);
//#endif


        return 0;
}

static void __exit dbfs_module_exit(void)
{
        // Implement exit module
	debugfs_remove_recursive(dir);
	printk("dbfs_paddr module exit\n");
}

module_init(dbfs_module_init);
module_exit(dbfs_module_exit);
