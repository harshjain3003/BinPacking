// Time table scheduling
#include<stdlib.h>
#include<stdio.h>
int a[10][10],l[10],bb[10],re[10][10],size=10;
struct box
{
	int length;
	int bredth;
	int no;
	char type;
	struct box *next;
	struct box *p;
}*top,*newnode,*temp,*rear,*temp2,*top2,*rear2,*temp3;

struct employee
{
	char type;
	int wage;
	int daily_wage=0;
}types[10];

void display(struct box *temp3)
{
	if(temp3==NULL)
	{
		printf("Underflow..!! ");
		system("PAUSE");
		return;
	}
	while(temp3!=NULL)
	{
		printf("%d --> %d --> %c \n",temp3->length,temp3->bredth,temp3->type);
		temp3=temp3->next;	
	}
	printf("!!! ");
	system("PAUSE");	
}


void push()
{
	input_push:
	int len,b;
	printf("Enter the working hour/person and number of persons required : ");
	scanf("%d %d",&len,&b);
	if (len>8)
	{
		printf("\n A person can work for a maximum of 8 hours.. ");
		goto input_push;
	}
	else if(b>size)
	{
		printf("\nAvailable number of persons are %d ",size);
		goto input_push;
	}
	
	newnode= (struct box *)malloc(sizeof(struct box));
	if(newnode==NULL)
	{
		printf("\nOut of memeory space..!! ");
		system("PAUSE");
		return;
	}
	
	printf("Enter the team of person required : ");
	scanf("%s",&newnode->type);
	
	newnode->length=len;
	newnode->bredth=b;
	
	newnode->next=NULL;
	newnode->p=NULL;
	newnode->no=(newnode->length*10)+newnode->bredth;
	
	temp=top;
	
	if(temp==NULL)
		rear=top=newnode;
	else
	{
		if(rear->no >= newnode->no)
		{
			newnode->p=rear;
			rear->next=newnode;
			rear=newnode;
			display(top);
			return;
		}
		else if(top->no <= newnode->no)
		{
			newnode->next=top;
			top->p=newnode;
			top=newnode;
			display(top);
			return;
		}
		while(temp!=NULL)
		{
		    if(temp->no <= newnode->no)
			{	
				newnode->next=temp;
				temp->p->next=newnode;
				newnode->p=temp->p;
				temp->p=newnode;	
				break;
			}
			temp=temp->next;
		}
	}
	display(top);
}

struct box * del_using_boxno(int no, struct box *&top, struct box *&rear)
{
	temp3=top;
	while(temp3!=NULL && temp3->no!=no)
		temp3=temp3->next;
	
	if(temp3==NULL)
	{
		printf("Data not Found..!! ");
		system("PAUSE");
		return NULL;
	}
	else
	{
		if(top==rear)
		{
			top=rear=NULL;
			free(temp3);
			return NULL;
		}
		else if(top->next==rear)
		{
			if(temp3==rear)
			{
				top->next=NULL;
				rear=top;
				free(temp3);
			}
			else
			{
				rear->p=NULL;
				top=rear;
				free(temp3);
			}
			return top;
		}
		else if(temp3==top)
		{
			top=top->next;
			free(temp3);
			return top;
		}
		else if(temp3==rear)
		{
			rear=rear->p;
			rear->next=NULL;
			free(temp3);
			return rear;
		}
		else
		{
			temp3->p->next=temp3->next;
			temp3->next->p=temp3->p;
			temp2=temp3->next;
			free(temp3);
			return temp2;
		}
	}
}

void dis(int a[][10], int l[], int bb[])
{
	int i,j,total=0;
	system("CLS");
	for(i=0;i<size;i++)
	{	
		printf("%c\t",types[i].type);
		for(j=0;j<10;j++)
		{
			printf("%3d ",a[i][j]);
			if (j==5)
				printf(" Break ");
		}
		printf("%4d \n",types[i].daily_wage);
		total+=types[i].daily_wage;
	}
	printf("\n\nTotal cost : %d\n",total);
	system("PAUSE");	
}

int allocate_length(int len,int b,char type, int a[][10],int  l[], int bb[],struct box *&top, struct box *&rear)
{
	int check=0,starti,startj,ii,j,i,f=0,gaps=1;
	starti=startj=-1;
	for(i=0;i<size;i++)
	{	
		if(l[i]>=len+2 && types[i].type==type)
		{	
			while(gaps!=0 && i+b-1<size && b>1 )
			{
				gaps=0;
				for(ii=i; ii<i+b ; ii++)
				{
					if(l[i]!=l[ii])
						gaps=1;
				}
				if(gaps==1)
				{
					i++;
					if(!(i+b-1<size))
						return f;
					continue;
				}
				else
					break;
			}
			
			if(startj==-1)
			{
				starti=i;
				startj=10-l[i];
			}
			check+=l[i];
			if (check>=len*b)
			{
				for(ii=starti;ii<starti+b;ii++)
				{
					for(j=startj;j<startj+len;j++)
					{
						a[ii][j]=temp->no;
						if (ii==starti+b-1)
							bb[j]=size-1-ii;
					}
					l[ii]=10-j;
					types[ii].daily_wage+=types[ii].wage*len;
				}
				f=1;
				temp=del_using_boxno(temp->no,top,rear);
				break;
			}				
		}
		
		else 
		{
			check=0;
			startj=-1;
		}
	}	
	return f;
}

void allocate()
{	
	int b,i,ii,len,f;
	temp=top;
	while(temp!=NULL)
	{	
		f=0;
		b=temp->bredth;
		len=temp->length;	
			
		f=allocate_length(len,b,temp->type,a,l,bb,top,rear);
				
		if(f==0)
			temp=temp->next;
		
		if(temp==NULL)
			break;
	}
}

void restart()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
			a[i][j]=0;
		}
	}
	for (i=0;i<10;i++)
	{
		l[i]=10;
		bb[i]=size;	
	}	
}

int main()
{
	system("CLS");
	top2=rear2=NULL;
	
	int i=0,j=0,choice=1,n=0,wages;
	char team='a';
	printf("\nEnter the total number of workers..!! ");
	scanf("%d",&size);
	
	while(n<size)	
	{	
		input_team:
		printf("\nEnter the number of people in team %c ", team);
		scanf("%d",&i);
		n+=i;
		if (n>size)
		{	
			printf("\nThe sum of number of people in teams exceed total number of people, try again..!! ");
			n-=i;
			goto input_team;
		}
		
		printf("\nEnter the hourly wage for members of team %c ", team);
		scanf("%d",&wages);
		for(;j<n;j++)
		{
			types[j].type=team;	
			types[j].wage=wages;
		}
		team++;
	}
	restart();
	
	while(choice!=0)
	{
		system("CLS");
		printf("\nMenu : \n1. New Job \n2. Display Pending Jobs \n3. Allocate \n4. Free Box \n0. Exit ");
		scanf("%d",&choice);
		
		if(choice==1)
			push();
		else if(choice==2)
			display(top);
		
		else if(choice==3)
		{
			if(top==NULL)
			{
				printf("\nEnter box data first ");
				system("PAUSE");
			}
			else		
			{
				allocate();				
				dis(a,l,bb);					
			}
		}
		else if(choice==4)
			restart();
	}
	
	temp=top;
	struct box *t;
	while(temp!=NULL)
	{
		t=temp;
		temp=temp->next;
		free(t);
	}
	return 0;
}
