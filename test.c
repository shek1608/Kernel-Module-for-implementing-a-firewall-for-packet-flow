#define _KERNEL_
#define MODULE
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops netfilter_ops_in;
static struct nf_hook_ops netfilter_ops_out;

unsigned int main_hook(unsigned int hooknum, 
			struct sk_buff **skb,
			const struct net_device *in,
			const struct net_device *out,
			int (*okfn)(struct sk_buff*))
{
	return NF_DROP;
}

int init_module()
{
	netfilter_ops_in.hook			= main_hook;
	netfilter_ops_in.pf			= PF_INET;
	netfilter_ops_in.hooknum		= NF_INET_PRE_ROUTING;
	netfilter_ops_in.priority		= NF_IP_PRI_FIRST;
	netfilter_ops_out.hook			= main_hook;
	netfilter_ops_out.pf			= PF_INET;
	netfilter_ops_out.hooknum		= NF_INET_POST_ROUTING;
	netfilter_ops_out.priority		= NF_IP_PRI_FIRST;
	nf_register_hook(&netfilter_ops_in);
	nf_register_hook(&netfilter_ops_out);

	return 0;
}

void cleanup_module()
{
	nf_unregister_hook(&netfilter_ops_in);
	nf_unregister_hook(&netfilter_ops_out);

}


