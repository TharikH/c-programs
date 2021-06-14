#include <mqueue.h>
#include <stdio.h>
#include<string.h>


int main() {

	mqd_t q1;
	
	char buf1[20],buf2[20],buf3[20];
	
	int pr1,pr2,pr3;
	printf(" Input message one : ");
	scanf("%s",buf1);
    printf("\n Input the priority of msg1: ");
	scanf("%d",&pr1);

	printf("\n Input message two : ");
	scanf("%s",buf2);
    printf("\n Input the priority of msg2: ");
	scanf("%d",&pr2);

	printf("\n Input message three : ");
	scanf("%s",buf3);
	printf("\n Input the priority of msg3: ");
	scanf("%d",&pr3);
	
	q1 = mq_open("/np",O_CREAT|O_RDWR,0666,NULL);
	if(q1 == -1) {
	 printf("Error");
	}
	mq_send(q1,buf1,strlen(buf1),pr1);
	mq_send(q1,buf2,strlen(buf2),pr2);
	mq_send(q1,buf3,strlen(buf3),pr3);
}
