#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define MAX_LOG_SIZE 10000

MODULE_LICENSE("GPL");

static struct dentry *dir, *inputdir, *ptreedir;
static struct task_struct *curr;

struct process_node {
	char *comm; //command
	int pid; //pid
	struct list_head list; // ptree linked list node for this process
};


static LIST_HEAD(head);

static char *logs;
struct debugfs_blob_wrapper *my_blob;

static void ptree_logging(void) {
	struct process_node *entry;
	int j = 0;
	
	logs = kmalloc(sizeof(char) * MAX_LOG_SIZE, GFP_KERNEL); // string arr

	list_for_each_entry(entry, &head, list) {
		j += snprintf(logs + j, 64, "%s (%d)\n", entry -> comm, entry -> pid);
	} // logs[j] = logging

	my_blob -> data = logs; // save all logs
	my_blob -> size = (unsigned long)strlen(logs);
}

static void insert_node(struct task_struct *task) {
	struct process_node *node;
	
	node = kmalloc(sizeof(struct process_node), GFP_KERNEL);
	
	if(!node) {
		printk("alloc failed\n");
		return;
	}
	
	node -> comm = task -> comm;
	node -> pid = task -> pid;
	list_add(&node -> list, &head);
}

static ssize_t write_pid_to_input(struct file *fp, 
                                const char __user *user_buffer, 
                                size_t length, 
                                loff_t *position)
{
        pid_t input_pid;

        sscanf(user_buffer, "%u", &input_pid);

		curr = pid_task(find_get_pid(input_pid), PIDTYPE_PID);
		if(curr == NULL) {
			printk("This process is not currently running\n");
		}

		// insert leaf process
		insert_node(curr);

		while(1) {
			// track upward and insert to linked list
			curr = curr -> parent;
			insert_node(curr);

			// if last insert was init(1)
			if(curr -> pid == 1) {
				break;
			}
		}
		
		ptree_logging();
		//reinitialize linkedlist for next one
		list_del_init(&head);

        return length;
}

static const struct file_operations dbfs_fops = {
        .write = write_pid_to_input,
};

static int __init dbfs_module_init(void)
{
        // Implement init module code

//#if 0
        dir = debugfs_create_dir("ptree", NULL);
        if (!dir) {
                printk("Cannot create ptree dir\n");
                return -1;
        }

        inputdir = debugfs_create_file("input", 0222, dir, NULL, &dbfs_fops);

		my_blob = (struct debugfs_blob_wrapper *)kmalloc(sizeof(struct debugfs_blob_wrapper), GFP_KERNEL);
       
		ptreedir = debugfs_create_blob("ptree", 0644, dir, my_blob); // Find suitable debugfs API
//#endif
	
	printk("dbfs_ptree module initialize done\n");

        return 0;
}

static void __exit dbfs_module_exit(void)
{
        // Implement exit module code
	// free
	kfree(my_blob);
	kfree(logs);

	// remove
	debugfs_remove_recursive(dir);
	printk("dbfs_ptree module exit\n");
}

module_init(dbfs_module_init);
module_exit(dbfs_module_exit);
