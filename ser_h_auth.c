//gcc -I/usr/include/libxml2 -L/usr/local/lib *.c -lxml2

#include "server_h.h"

void close_all_sfd()
{
	printf("DDD\n");
	close(con_a_fd);
}

int read_data(int *fd)
{
	con_a_fd=*fd;
	usleep(500000);
	int ret=0;
	bzero(token_buff,1024);
	ret=recv(con_a_fd,token_buff,1023,MSG_WAITALL);
	if(ret==-1 || ret==0){
		printf("recvtimeout!%d\n",con_a_fd);
		if(auth_count-->1){
			read_data(fd);
		}
		else {
			close_all_sfd();
			return ret;
		}
	}
	else{
		printf("ret=%d, token_buff: %s\n",ret,token_buff);
		return ret;
	}
}

int find_pkt()
{
	char *tmp1=NULL,*tmp2=NULL;
	tmp1=strstr(token_buff+8,"<gwsctrl>");
	tmp2=strstr(token_buff+8,"</gwsctrl>");
	if(tmp1 && tmp2){
		printf("find pkt!\n");
		bzero(token2save_buff,1024);
		strncat(token2save_buff,tmp1,tmp2-tmp1+10);
		printf("pkt is %s\n",token2save_buff);
		return 0;
	}
	else{
		printf("can't find pkt!\n");
		return 1;
	}
}

int get_token()
{
	int len=0;
    xmlDocPtr doc;
    xmlNodePtr root,node,detail;
    xmlChar *name,*value;
    len=strlen(token2save_buff)+1;
    doc=xmlParseMemory(token2save_buff,len);    //parse xml in memory 字符串转为XML文档
    if(doc==NULL){
        printf("doc == null\n");
        return -1;
    }
    printf("pkt1 is %s\n",token2save_buff);
    root=xmlDocGetRootElement(doc);//获取XML文档根节点
    for(node=root->children;node;node=node->next){//XML节点指针指向第一个子节点
        if(xmlStrcasecmp(node->name,"token")==0){//判断字符串是否相等(忽略大小写)
        	value=xmlGetProp(node,"val"); //获得节点的属性值
            name=xmlNodeGetContent(node);//获得节点的内容
            printf("this is: %s\ntoken is: %s\n",(char*)value,token);   //get value, CDATA is not parse and don't take into value
            if(!(strncmp(value,token,strlen(token)))){
            	printf("OK\n");
            	auth_count=0;
            }
            else
            	return -1;
            xmlFree(name);
            xmlFree(value);
            break;
        }
    }
    if(node==NULL){
        printf("no node = token\n");
	    xmlFreeDoc(doc);
        return -1;
    }
    xmlFreeDoc(doc);
    return 0;
}

