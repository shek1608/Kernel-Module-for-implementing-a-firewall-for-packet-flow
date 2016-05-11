#define __KERNEL__
#define MODULE
#include <linux/ip.h>             
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/netdevice.h>      
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h> 
#include <linux/skbuff.h>         
#include <linux/udp.h>                    
static struct nf_hook_ops netfilter_ops;                        
static unsigned char *ip_address = "\x0A\xD3\x37\x02";
static char *interface = "lo";                          
unsigned char *port = "\x00\x17";                       
struct sk_buff *sock_buff;                              
struct udphdr *udp_header;                              
unsigned int main_hook(unsigned int hooknum,
                  struct sk_buff **skb,
                  const struct net_device *in,
                  const struct net_device *out,
                  int (*okfn)(struct sk_buff*))


{
  if(strcmp(in->name,interface) == 0){ return NF_DROP; }     
  struct iphdr* iph = ip_hdr(skb);
  sock_buff = *skb;
  if(!sock_buff){ return NF_ACCEPT; }                   
  if(!(iph)){ return NF_ACCEPT; }              
  if(iph->saddr == *(unsigned int*)ip_address){ return NF_DROP; }
                
  
if(iph->protocol != 17){ return NF_ACCEPT; }                 
udp_header = (struct udphdr *)(sock_buff->data + (iph->ihl *4)); 
if((udp_header->dest) == *(unsigned short*)port){ return NF_DROP; }
return NF_ACCEPT;
}
int init_module()
{
        netfilter_ops.hook              =       main_hook;
        netfilter_ops.pf                =       PF_INET;        
        netfilter_ops.hooknum           =       NF_INET_PRE_ROUTING;
        netfilter_ops.priority          =       NF_IP_PRI_FIRST;
        nf_register_hook(&netfilter_ops);
        
return 0;
}
void cleanup_module() { nf_unregister_hook(&netfilter_ops); }
