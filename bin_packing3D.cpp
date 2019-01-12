#include<stdlib.h>
#include<stdio.h>
#define size 10
int a[5][size][size],saveh[size][size],l[5][size],bb[5][size],re[size][size],ar=size*size,aa[5][size][size],aar=size*size,al[5][size],abb[5][size];
int max_h=0;
struct box
{
	int length;
	int bredth;
	int height;
	long no;
	struct box *next;
	struct box *p;
}*top,*newnode,*temp,*rear,*temp2,*top2,*rear2,*temp3;

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
		printf("%d --> %d --> %d \n",temp3->length,temp3->bredth,temp3->height);
		temp3=temp3->next;	
	}
	printf("!!! ");
	system("PAUSE");	
}

void copy_ll()
{
	temp3=top;
	if(temp3==NULL)
	{
		printf("Underflow..!! ");
		system("PAUSE");
		return;
	}
	
	newnode= (struct box *)malloc(sizeof(struct box));
	if(newnode==NULL)
	{
		printf("\nOut of memeory space..!! ");
		system("PAUSE");
		return;
	}
	newnode->next=NULL;
	newnode->p=NULL;
	newnode->bredth=temp3->bredth;
	newnode->length=temp3->length;
	newnode->height=temp3->height;
	newnode->no=(newnode->height*1000)+(newnode->length*10)+newnode->bredth;
	
	top2=rear2=newnode;
	temp3=temp3->next;	
	while(temp3!=NULL)
	{
		newnode= (struct box *)malloc(sizeof(struct box));
		if(newnode==NULL)
		{
			printf("\nOut of memeory space..!! ");
			system("PAUSE");
			return;
		}
		newnode->next=NULL;
		newnode->p=NULL;
		newnode->bredth=temp3->bredth;
		newnode->length=temp3->length;
		newnode->height=temp3->height;
		newnode->no=(newnode->height*1000)+(newnode->length*10)+newnode->bredth;
		
		newnode->p=rear2;
		rear2->next=newnode;
		rear2=newnode;
		
		temp3=temp3->next;
	}
}

void push()
{
	int len,b,h;
	newnode= (struct box *)malloc(sizeof(struct box));
	if(newnode==NULL)
	{
		printf("\nOut of memeory space..!! ");
		system("PAUSE");
		return;
	}
	
	printf("Enter the Length, Bredth ,Height of the box : ");
	scanf("%d %d %d",&len,&b,&h);
	if (len>b)
	{
		newnode->length=len;
		newnode->bredth=b;
	}
	else
	{
		newnode->length=b;
		newnode->bredth=len;
	}
	newnode->height=h;
	newnode->next=NULL;
	newnode->p=NULL;
	newnode->no=(newnode->height*1000)+(newnode->length*10)+newnode->bredth;
	
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

void dis(int a[][size][size], int l[][size], int bb[][size], int ar)
{
	int i,j,k;
	for(k=0;k<max_h;k++)
	{	
		system("CLS");
		printf("Height : %d \n\n",k+1);
		for(i=0;i<size;i++)
		{	
			for(j=0;j<size;j++)
				printf("%4d ",a[k][i][j]);
			printf("%3d \n",l[k][i]);
		}
		for(i=0;i<size;i++)
			printf("%4d ",bb[k][i]);
		printf("\n %d \n",ar);
		system("PAUSE");	
	}
}

int allocate_b(int len,int b, int a[][size][size], int l[][size], int bb[][size],struct box *&top, struct box *&rear,int h,int sent);

int allocate_length(int len,int b, int a[][size][size],int  l[][size], int bb[][size],struct box *&top, struct box *&rear,int h=0,int sent=0)
{
	for(h=0;h<5;h++)
	{	
		again:
		if(h+temp->height>5 && h<5)
			return 0;
		int check=0,starti,startj,ii,k,j,i,f=0,gaps=1;
		starti=startj=-1;
		
		for(i=0;i<size;i++)
		{	
			if(l[h][i]>=len)
			{	
				while(gaps!=0 && i+b-1<size && b>1)
				{
					gaps=0;
					for(ii=i; ii<i+b ; ii++)
					{
						if(l[h][i]!=l[h][ii])
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
					startj=size-l[h][i];
				}
				if(starti+b-1>=size)
					break;
					
	
	
				int qq,flag=1;
				for(qq=h;qq<h+temp->height and qq<5;qq++)  		   	// check if the above layers are empty or not
				{
					if(!(l[qq][i]>=len))
					{
						flag=0;
						break;
					}
				}
				if (flag==0)
				{
					h++;
					goto again;
				}
	
				check+=l[h][i];
	
	
				if (check>=len*b)
				{	
					if(max_h<temp->height+h)						// check if the box height is still lesser than the height of container
						max_h=temp->height+h;
			
					for(ii=starti;ii<starti+b;ii++)
					{
						for(j=startj;j<startj+len;j++)
						{
							for(k=h;k<h+temp->height;k++)
							{
								a[k][ii][j]=temp->no;
								if (ii==starti+b-1)
									bb[k][j]=size-1-ii;
								if(j==startj+len-1)
									l[k][ii]=size-j-1;			
							}
						}
					}
					f=1;
					temp=del_using_boxno(temp->no,top,rear);
					return f;
				}
			}
			
			else 
			{
				check=0;
				startj=-1;
			}
		}
		f=allocate_b(len,b, a,l, bb,top, rear, h,1);
		if(f==1)
			return f;	
	}
	return 0;
}

int allocate_b(int len,int b, int a[][size][size], int l[][size], int bb[][size],struct box *&top, struct box *&rear,int h=0,int sent=0)
{	

	int e=5,s=0;
	if (sent==1)
	{
		e=h+1;
		s=h;
	}
	for(h=s;h<e;h++)
	{
		again:
		if(h+temp->height>5 && h<e)
		{
			temp=temp->next;
			return 1;
		}
		int check=0,starti,startj,ii,k,j,i,f=0;
		starti=startj=-1;
		for(i=0;i<size;i++)
		{
			if(l[h][i]>=b)
			{	
				if(startj==-1)
				{
					starti=i;
					startj=size-l[h][i];
				}
				if(starti+len-1>=size)
					break;
				
				int qq,flag=1;
				for(qq=h;qq<h+temp->height and qq<5;qq++)  		   	// check if the above layers are empty or not
				{
					if(!(l[qq][i]>=b))
					{
						flag=0;
						break;
					}
				}
				if (flag==0)
				{
					h++;
					goto again;
				}
				
				check+=l[h][i];
				if (check>=len*b)
				{	
					if(max_h<temp->height+h)
						max_h=temp->height+h;
					for(ii=starti;ii<starti+len;ii++)
					{
						for(j=startj;j<startj+b;j++)
						{
							for(k=h;k<h+temp->height;k++)
							{
								a[k][ii][j]=temp->no;
								if (ii==starti+len-1)
									bb[k][j]=size-1-ii;
								if(j==startj+b-1)
									l[k][ii]=size-j-1;			
							}
						}
					}
					f=1;
					temp=del_using_boxno(temp->no,top,rear);
					return f;
				}				
			}
			
			else 
			{
				check=0;
				startj=-1;
			}
		}
	}
	return 0;
}

int allocate_d(int len, int b,int s,int a[][size][size], int l[][size], int bb[][size],struct box *&top, struct box *&rear,int h=0)
{
	if(h+temp->height>5)
	{
		temp=temp->next;
		return 1;
	}
	int ii,j,k;

	if(max_h<temp->height+h)
		max_h=temp->height;	
	for(ii=size-len;ii<size;ii++)
	{
		for(j=s;j<s+b;j++)
		{
			for(k=h;k<h+temp->height;k++)
			{
				a[k][ii][j]=temp->no;
				if (ii==size-len)
					bb[k][j]-=len;
				if (j==s+b-1)
					l[k][ii]-=b;
			}
		}
	}
	temp=del_using_boxno(temp->no,top,rear);
	return 1;				
}

void allocate()
{	
	int b,i,ii,len,f,jump;
	temp=top;
	while(temp!=NULL)
	{	
		f=jump=0;
		b=temp->bredth;
		len=temp->length;	
		
		for(ii=0;ii<=size-b;ii++)
			if(bb[0][ii]==len)
				break;
				
		if(bb[0][ii]==len && len!=size && ii!=size+1-b && ii+b<size)
		{		
			int s=ii;
			for(i=ii;i<ii+b ;i++)
				if(!bb[0][i]==len)
				{	
					jump=1;
					break;
				}
			if(jump==0)
				f=allocate_d(len,b,s,a,l,bb,top,rear);
			
		}
		if (f==0)
			f=allocate_length(len,b,a,l,bb,top,rear);
				
		if (f==0)
			f=allocate_b(len,b,a,l,bb,top,rear);
		
		if(f==0)
			temp=temp->next;
		
		if(temp==NULL)
			break;
	}
}


void allocate2()
{	
	int b,i,ii,len,f;
	temp=top2;
	while(temp!=NULL)
	{	
		f=0;
		b=temp->bredth;
		len=temp->length;
				
		f=allocate_length(len,b,aa,al,abb,top2,rear2);
		if (f==0)
		{
			f=allocate_b(len,b,aa,al,abb,top2,rear2);
		}
		if(f==0)
		{
			temp=temp->next;
		}
	}
}

int main()
{
	top2=rear2=NULL;
	int i,j,k;
	for(k=0;k<5;k++)
	{
		for(i=0;i<size;i++)
		{
			for (j=0;j<size;j++)
				a[k][i][j]='\0';
			l[k][i]=al[k][i]=size;
			bb[k][i]=abb[k][i]=size;
		}
	}
	int choice=1;
	while(choice!=0)
	{
		system("CLS");
		printf("\nMenu : \n1. New Box \n2. Display \n3. Allocate \n0. Exit ");
		scanf("%d",&choice);
		
		if(choice==1)
			push();
		else if(choice==2)
		{
			display(top);
			display(top2);
		}
		else if(choice==3)
		{
			if(top==NULL)
			{
				printf("\nEnter box data first ");
				system("PAUSE");
			}
			else		
			{
				copy_ll();
				ar=aar=0;
				allocate();
				system("PAUSE");
				allocate2();
				system("PAUSE");
				for(k=0;k<max_h;k++)	
				{
					for(i=0;i<size;i++)
					{
						ar+=l[k][i];
						aar+=al[k][i];
					}
				}
				if (max_h==0)
				{
					printf("No allotment done..!! ");
					system("PAUSE");
				}
				else if(ar<=aar)
					dis(a,l,bb,ar);
				else if (ar>aar)
					dis(aa,al,abb,aar);
/*				else
				{
					printf("2 possible solutions : ");
					system("PAUSE");
					dis(a,l,bb,ar);
					dis(aa,al,abb,aar);	
				}	
*/			}
		}
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
