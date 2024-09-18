#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

void display() ;
void Sorted_Insertion(int s_no);
void search(char search_name[]);
void Edit(char edit_name[]);
struct list
{
	int s_no;
	char name[50], email[50], address[100];
	char mobile[10];
	struct list *next;
}*head=NULL;
struct lstack
{
    struct list* data;
    struct lstack *next;
}*top = NULL;
void pushintostack(struct list* n)
{
    struct lstack *l = (struct lstack*)malloc(sizeof(struct lstack));
    l->next=NULL;
    l->data = n;
    if(top == NULL)
    {
        top = l;
        return;
    }
    else
    {
        l->next = top;
        top = l;
    }

}
struct list* popfromstack()
{
    if(top == NULL)
    {
        printf("\nStack is empty");
        return NULL;
    }
    struct list* n=top->data;
    struct lstack* temp=top;
    top=top->next;
    free(temp);
    return n;
}

void Sorted_Insertion(int s_no)
{
	struct list *nn;
	nn=(struct list *)malloc(sizeof(struct list));
	nn->s_no = s_no;
	printf("\nName          : ");
	fflush(stdin);
	scanf("%[^\n]s",nn->name);
	fflush(stdin);
//	cout<<"Mobile Number : ";
//	cin>>nn->mobile;
	printf("Mobile Number : ");
	scanf("%s",nn->mobile);
	cout<<"Email         : ";
	cin>>nn->email;
	//printf("Email         : ");
	//scanf("%s",nn->email);
	printf("Address       : ");
	scanf("%s",nn->address);
	nn->next=NULL;
	if(head==NULL)
		head=nn;
	struct list *temp=head;
	if(nn->s_no<temp->s_no)
	{
		nn->next=head;
		head=nn;
	}
	else if(nn->s_no>temp->s_no)
	{
		while((temp->next!=NULL)&&(nn->s_no>temp->next->s_no))
				temp=temp->next;
		if(temp->next!=NULL)
		{
			nn->next=temp->next;
			temp->next=nn;
		}
		else if(temp->next==NULL)
		{
			temp->next=nn;
			nn->next = NULL;
		}
	}
//	printf("\n\nList:\n-----\n");
	display();
}

void search(char search_name[])
{
	struct list *temp=head;
	if(temp==NULL)
		printf("\nThere is no element in the list");
	else
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(!(strcmp(search_name,temp->name)))
			{
				cout<<"\n\n-------------------------------------\n\nName          : "<<temp->name<<"\nMobile Number : "<<temp->mobile<<"\nEmail         : "<<temp->email<<"\nAddress       : "<<temp->address<<"\n\n-------------------------------------";
				return;
			}
		}
	}
	cout<<"Not found!";
}
void display()
{
	struct list *temp=head;
	if(temp==NULL)
		printf("There is no element in the list");
	else
	{
		printf("\n\n--------\nDetails:\n--------");
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			cout<<"\n\n-------------------------------------\n\nName          : "<<temp->name<<"\nMobile Number : "<<temp->mobile<<"\nEmail         : "<<temp->email<<"\nAddress       : "<<temp->address<<"\n\n-------------------------------------";
			//printf("Name          : %s, \nMobile Number : %d, \nEmail         : %s, \nAddress       : %s\n",temp->name, temp->mobile, temp->email, temp->address);
		}
	 	//printf("NULL\n");
	}
}
void Edit_Details(char edit_name[])
{
	struct list *temp=head;
	int option;
	if(temp==NULL)
		printf("There is no element in the list");
	else
	{
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			if(!(strcmp(edit_name,temp->name)))
			{
				printf("\nEnter the field to edit (1-Name, 2-Number, 3-Email, 4-Address):");
				scanf("%d", &option);
				switch(option)
				{
					case 1: printf("\nEnter Name : ");
							fflush(stdin);
							scanf("%[^\n]s", temp->name);
							fflush(stdin);
							//strcpy(temp->name,edit_name);
							printf("Name Updated");
							break;
					case 2: printf("\nEnter number: ");
							scanf("%s", temp->mobile);
							printf("Mobile Number Updated");
							break;
					case 3: printf("\nEnter email: ");
							scanf("%s", temp->email);
							printf("Email Updated");
							break;
					case 4: printf("\nEnter address: ");
							scanf("%s", temp->address);
							printf("Address Updated");
							break;
				}
				break;
			}
		}
	}
}

void Delete_Contact(char edit_name[])
{
	struct list *temp=head, *del;
	int option;
	if(temp==NULL)
		printf("There is no element in the list");
	else if(!strcmp( edit_name, head->name))
	{
	    del=head;
		head = head->next;
		pushintostack(del);
	}
	else
	{
		for(temp=head;temp->next!=NULL;temp=temp->next)
		{
			if(!(strcmp(edit_name,temp->next->name)))
			{
				del = temp->next;
				if(temp->next->next != NULL)
					temp->next = temp->next->next;
				else
					temp->next = NULL;
				pushintostack(del);
				break;
			}
		}
	}
	printf("\nThe contact is deleted.");
}
void Restore_Contact()
{
    if(top == NULL)
    {
        printf("\nNo recently deleted.");
        return;
    }
    struct list* n=popfromstack();
    if(n->next == head)
    {
        head=n;
    }
    else
    {
        struct list*temp;
        for(temp=head;;temp=temp->next)
		{
			if(n->next == temp->next)
			{
				temp->next = n;
				break;
			}
			if(temp->next==NULL)
                break;
		}
    }
}
void add_to_Linked_List(struct list a)
{
    struct list *nn;
	nn=(struct list *)malloc(sizeof(struct list));
	strcpy(nn->address,a.address);
	strcpy(nn->email,a.email);
	strcpy(nn->mobile,a.mobile);
	strcpy(nn->name,a.name);
	nn->s_no = a.s_no;
	nn->next = NULL;
	if(head == NULL)
        head = nn;
    else
    {
        struct list*temp=head;
        for(;temp->next!=NULL;temp=temp->next);
        temp->next = nn;

    }
}
void load_Linkedlist()
{
    FILE *fptr;
    fptr=fopen("Contact.dat","rb");
    if(fptr == NULL)
    {
        head=NULL;
        return;
    }
    struct list a;
    while(fread(&a,sizeof(struct list),1,fptr))
    {
        add_to_Linked_List(a);
    }
    fclose(fptr);

}
void write_Linkedlist()
{
    FILE *fptr;
    fptr=fopen("Contact.dat","wb");
    struct list a;
    struct list* temp=head;
    for(;temp!=NULL;temp=temp->next)
        fwrite(temp,sizeof(struct list),1,fptr);
    fclose(fptr);

}
void freestack()
{
    struct lstack* d;
    while(top!=NULL)
    {
       free(top->data);
       d=top;
       top=top->next;
       free(d);
    }
}
int main()
{
	int choice,con,s_no;
	char element[50], arr[50];
	load_Linkedlist();
	printf("----------------CONTACT MANAGEMENT SYSTEM-----------------\n");      
	printf("1.AddContact\n2.Search\n3.Edit\n4.Delete\n5.Display\n6.Restore\n");
	printf("----------------------------------------------------------\n");
	while(1)	{
		fflush(stdin);
		printf("\n\nEnter the choice:");
		scanf("%d",&choice);
		switch(choice) 	{
			case 1:
				printf("\nEnter the number:");
				scanf("%d",&s_no);
				Sorted_Insertion(s_no);
				break;
			case 2:
				printf("\nEnter the contact name to search:");
				fflush(stdin);
				scanf("%[^\n]s",arr);
				fflush(stdin);
				search(arr);
				break;
			case 3:
				printf("\nEnter the contact name to edit:");
				fflush(stdin);
				scanf("%[^\n]s",element);
				fflush(stdin);
				Edit_Details(element);
				break;
			case 4:
				printf("\nEnter the contact name to delete:");
				fflush(stdin);
				scanf("%[^\n]s",element);
				fflush(stdin);
				Delete_Contact(element);
				break;
			case 5:
				display();
				// return 0;
				break;
            case 6:
                Restore_Contact();
                break;
			default:
				printf("\nProgram Terminated!!!");
				freestack();
				write_Linkedlist();
				exit(0);
		}

	}
	return 0;
}
