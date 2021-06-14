#include <mqueue.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int main() {
mqd_t q;
char *buf;
struct mq_attr *attr1;
int prio;
attr1 = malloc(sizeof(struct mq_attr));

q = mq_open("/np",O_RDWR);

if(q == -1) {
 printf("Error");
}

buf = malloc(10*sizeof(char));
mq_getattr(q, attr1);

mq_receive(q,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\nMessage = %s\n",buf);


mq_receive(q,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\nMessage = %s\n",buf);


mq_receive(q,buf,attr1->mq_msgsize,&prio);
printf("Priority= %d",prio);
printf("\nMessage = %s\n",buf);

}
