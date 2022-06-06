/*Design And Development by
Satheesh V
User_name = Satheesh-16*/







#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

int staff_iter=-1,student_iter=-1,com_iter=-1,breakAndlunch=0,dinner=0;

int student_Login();
int student_work(int);
int staff_Login();
int staff_work();
int Admin_Login();
int FAQ();
int Support();

struct food_fee{
	float break_fast,lunch,dinner,total_food;
};
struct Student_details   //student details saving through stucture 
{
	char student_name[30];
	char student_email[30],student_pass[30];
	char gender[30],duration[40];
	char address[100],place[30];
	int Room_no;
	int age;
	struct food_fee food;
	float rent,payable_amount;
	
}student[100];

struct Staff_details
{
	char staff_name[30];
	char staff_domain[30];
	char staff_username[30],staff_password[30];
	char staff_email[30];
	int staff_id_no;
}staff[30];

struct complaint_forum
{
	int room_no;
	char student_name[30];
	char complaint[1200];
}com[20];

int check_adminLogin(char a[],char b[]){         //Login checking for admin
	FILE* fptr;
	char admin_mail[50],admin_pass[30];
	fptr = fopen("Admin_Data.txt","r");
	if(fptr==NULL){
		printf("File not opened");
	}
	else{
		while(fscanf(fptr,"%s %s",admin_mail,admin_pass)!=EOF){
			if(strcmp(admin_mail,a)==0 && strcmp(b,admin_pass)==0){
	//			printf("login was successfull\n");
				return 1;
			}
		}
	}
	return 0;
}

int check_studentLogin(char a[],char b[]){         //Login checking for admin
	FILE* fptr;
	char stu_mail[50],stu_pass[30],i[10];
	fptr = fopen("student_login_details.txt","r");
	if(fptr==NULL){
		printf("File not opened");
	}
	else{
		while(fscanf(fptr,"%s %s %s",stu_mail,stu_pass,i)!=EOF){
			if(strcmp(stu_mail,a)==0 && strcmp(b,stu_pass)==0){
	//			printf("login was successfull\n");
				return atoi(i);
			}
		}
	}
	return -1;
}

int check_Stafflogin(char a[],char b[])
{
	FILE* fptr;
	char sta_mail[50],sta_pass[30],i[10];
	fptr = fopen("staff_login_details.txt","r");
	if(fptr==NULL){
		printf("File not opened");
	}
	else{
		while(fscanf(fptr,"%s %s %s",sta_mail,sta_pass,i)!=EOF){
			if(strcmp(sta_mail,a)==0 && strcmp(b,sta_pass)==0){
	//			printf("login was successfull\n");
				return 1;
			}
		}
	}
	return -1;
}

int main()
{
	int choice,out=0;
	printf("----------------------------Welcome to the KoHo Hostel Service--------------------------\n");
	do{
		printf("\n1. Student Login\t2. Staff Login\t\t3. Admin Login\n4. FAQ\t\t\t5. Support/Help\t\t6. Exit\n");
		printf("\nEnter Option to Get in : ");
		scanf("%d",&choice); //choice = saving choice for each case
		switch(choice){
			case 1:
				out = student_Login();
				break;
			case 2:
				out = staff_Login();
				break;
			case 3:
				out = Admin_Login();
				break;
			case 4:
				out = FAQ();
				break;
			case 5:
				out = Support();
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("Enter Correct Option!!!");
				break;
		}
	}while(out);
	return 0;
}

int student_Login() //student login checking 
{
	int log_acceptance=-1;                          //log_acceptance = checking student login
	char user_email[30],user_password[30];
	printf("\nHI, There\n");
	printf("Enter your login email : ");
	scanf("%s",user_email);
	printf("\nEnter Password : ");
	scanf("%s",user_password);
	log_acceptance = check_studentLogin(user_email,user_password);
	if(log_acceptance>-1){
		student_work(log_acceptance);
	}
	else{
		printf("\nNo such email and password existed\n");
	}
	return 1;
}

int student_work(int student_numb)
{
	int stu_choice,i;
	printf("\n11. Room Details\t\t12. Payment Details\t\t13. Order Food\n14. Generate Bill\t\t15. Complaint Forum\t\t16. EXIT\n");
	printf("\nEnter Choice : ");
	scanf("%d",&stu_choice);  // selecting student choice..
	student[student_numb].payable_amount=student[student_numb].rent;
	switch(stu_choice)
	{
		case 11:
			printf("\nRoom Number\t\tDuration\t\tRent\t\t\n");
			printf("%d\t\t%s\t\t%.3f",student[student_numb].Room_no,student[student_numb].duration,student[student_numb].rent);
			printf("\n");
			break;
				
		case 12:
			printf("\nStudent Name\t\tDate\t\tRoom Rent\t\tFood Fee\n");
			student[student_numb].payable_amount += student[student_numb].food.total_food;
			printf("%s\t\t%s\t\t%.3f\t\t%.3f",student[student_numb].student_name,"12/12/12",student[student_numb].rent,student[student_numb].food.total_food);
			printf("\nTotal Amount to be paid : %.2f",student[student_numb].payable_amount);
			printf("\n");
			break;
		case 13:
			printf("\n##Welcome to Ordering##\n");
			int foo_choice;
			printf("Break-fast ===>   40.00\nLunch===>   60.00\nDinner===>   70.00\n");
			printf("Order Food for 111. 1 Month Or 112. Particular day\n");
			printf("Enter Your Choice : ");
			scanf("%d",&foo_choice);
			switch(foo_choice)
			{
				case 111:
					//for a month each part is multiply by 30
					printf("\nTotal cost of Three times food per day for 1 month : Rs.5100.00\n");
					student[student_numb].food.break_fast = 30*40;
					student[student_numb].food.lunch = 30*60;
					student[student_numb].food.dinner = 30*70;
					student[student_numb].food.total_food += student[student_numb].food.break_fast+student[student_numb].food.lunch+student[student_numb].food.dinner;
					breakAndlunch++; // for each case breakfast and lunch can be added to the list
					dinner++;
					break;
				case 112:
					printf("\nNumber of days required Food : ");
					int days_food,food_choice;
					scanf("%d",&days_food);
					printf("\nEnter 1 if you want breakfast+lunch only else enter 2 if you want dinner only : ");
					scanf("%d",&food_choice);
					if(food_choice==1){
						student[student_numb].food.break_fast = days_food*(40);
						student[student_numb].food.lunch = days_food*(60);
						student[student_numb].food.total_food += student[student_numb].food.break_fast+student[student_numb].food.lunch;
						breakAndlunch++;
					}
					else if(food_choice==2){
						student[student_numb].food.dinner = days_food*(70);
						student[student_numb].food.total_food += student[student_numb].food.dinner;
						dinner++;
					}
					else{
						printf("\nWrong choice!!!\n");
					}
			}
			printf("\n");
			break;
		case 14: // for generating receipt and store as a file...
			printf("\n----------------------------------------------------------------------------------------------------------------\n");
			printf("Student Name \t Room no \t Room Rent \t Food Fee\n");
			int receipt;
			student[student_numb].payable_amount = student[student_numb].rent+student[student_numb].food.total_food;
			printf("------------------------------------------------------------------------------------------------------------------\n");
			printf("%s\t\t%d\t\t%.2f\t\t%.2f",student[student_numb].student_name,student[student_numb].Room_no,student[student_numb].rent,student[student_numb].food.total_food);
			printf(" \nTotal Fee : %.3f",student[student_numb].payable_amount);
			printf("\nEnter 1 for bill receipt : ");
			scanf("%d",&receipt);
			if(receipt){
				FILE* ptr;
				ptr = fopen("Receipt.txt","w+");
				if(ptr==NULL){
					printf("Receipt not generated\n");
				}
				else{
					fprintf(ptr,"Student Name : %s\nStudent Room Number : %d\nRoom Rent : %.2f\nFood Fee : %.2f\n",student[student_numb].student_name,student[student_numb].Room_no,student[student_numb].rent,student[student_numb].food.total_food);
					fprintf(ptr,"\nTotal Amount To paid %.3f",student[student_numb].payable_amount);
				}
				fclose(ptr);
			}
			printf("\n");
			break;
		case 15:
			com_iter++;
			printf("\nWelcome to the complaint forum\n");
			printf("Enter your name : ");
			scanf("%s",com[com_iter].student_name);
			printf("Enter Your Room Number : ");
			scanf("%d",&com[com_iter].room_no);
			printf("Write your complaint in Single line and for space add underscore(_) : ");
			scanf("%s",com[com_iter].complaint);
			FILE* fptr;
			fptr = fopen("Complaint_form.txt","a+"); // opening text file for saving as a file...
			if(fptr == NULL){
				printf("Form not opened\n");
			}
			else{
				fprintf(fptr,"\nName :  %s\t\t Room Number : %d\nComplaint : %s",com[com_iter].student_name,com[com_iter].room_no,com[com_iter].complaint);
			}
			fclose(fptr);
			break;
		case 16:
			main();
			break;
		default:
			printf("\nYou Enteres wrong choice!!!");
			break;
	}
	return student_work(student_numb);
}


int staff_Login()
{
	int log_acceptance=-1;                          //log_acceptance = checking student login
	char user_email[30],user_password[30];
	printf("\nHI, There\n");
	printf("Enter your login id : ");
	scanf("%s",user_email);
	printf("\nEnter Password : ");
	scanf("%s",user_password);
	log_acceptance = check_Stafflogin(user_email,user_password);
	if(log_acceptance>-1){
		staff_work();
	}
	else{
		printf("\nNo such email and password existed\n");
	}
	return 1;
}

int staff_work()
{
	int choice_for_work;
	int i;
	printf("\n11. Student Registration\t12. Student Details\t13. Student Details by Room No\n14. Number of meals preparation list\t15. Complaints Forum\t16. Exit\n");
	printf("Enter your choice : ");
	scanf("%d",&choice_for_work);
	switch(choice_for_work)
	{
		case 11:
			student_iter++;
			printf("Enter Student Name : ");
			scanf("%s",student[student_iter].student_name);
			printf("Enter Email Address : ");
			scanf("%s",student[student_iter].student_email);
			printf("Enter Password : ");
			scanf("%s",student[student_iter].student_pass);
			printf("Enter Gender : ");
			scanf("%s",student[student_iter].gender);
			printf("Enter Address : ");
			scanf("%s",student[student_iter].address);
			printf("Enter place : ");
			scanf("%s",student[student_iter].place);
			printf("Allot Room Number : ");
			scanf("%d",&student[student_iter].Room_no);
			printf("Enter Rent : ");
			scanf("%f",&student[student_iter].rent);
			printf("Enter Duration Allotment : ");
			scanf("%s",student[student_iter].duration);
			student[student_iter].food.break_fast = 0.00;
			student[student_iter].food.lunch = 0.00;
			student[student_iter].food.dinner = 0.00;
			student[student_iter].food.total_food = 0.00;
			FILE* fptr;
			fptr = fopen("student_details.txt","a+");
			if(fptr == NULL){
				printf("File not opened");
			}
			else{
				fprintf(fptr,"\nStudent Name = %s\nEmail : %s\nPassword : %s\nGender : %s\nAddress : %s\nRoom No : %d\nRoom Rent : %.2f\n",student[student_iter].student_name,student[student_iter].student_email,student[student_iter].student_pass,student[student_iter].gender,student[student_iter].address,student[student_iter].Room_no,student[student_iter].rent);
			}
			fclose(fptr);
			fptr = fopen("student_login_details.txt","a+");
			if(fptr == NULL){
				printf("File not opened");
			}
			else{
				fprintf(fptr,"%s\n%s\n%d\n",student[student_iter].student_email,student[student_iter].student_pass,student_iter);
			}
			fclose(fptr);
			break;
		case 12:
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("Student Name\t\tEmail\t\t\tGender\t\tAddress\t\t\tPlace\t\tRoom No\\tt\tRent Amount\n");
			printf("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			for(i=0;i<=student_iter;i++){
				printf("%s\t%s\t%s\t%s\t%s\t%d\t%.2f",student[i].student_name,student[i].student_email,student[i].gender,student[i].address,student[i].place,student[i].Room_no,student[i].rent);
				printf("\n");
			}
			break;
		case 13:
			printf("Enter room no : ");
			int r_n,r_no_no;  // r_n - room no for checking
			scanf("%d",&r_n);
			for(i=0;i<=student_iter;i++){
				if(r_n == student[i].Room_no){
					r_no_no = 1;
					printf("--------------------------------------------------------------------------------------------------\n");
					printf("Student Name\tEmail\t\tGender\tAddress\t\t\tPlace\tRoom No\t\tRent Amount\n");
					printf("--------------------------------------------------------------------------------------------------\n");
					printf("%s\t%s\t%s\t%s\t%s\t%d\t%.2f\n",student[i].student_name,student[i].student_email,student[i].gender,student[i].address,student[i].place,student[i].Room_no,student[i].rent);
					break;
				}
				else{
					r_no_no = 0;
				}
			}
			if(r_no_no == 0){
				printf("No such room is available");
			}
			break;
		case 14: // for showing the number of meals prepare for the day
			printf("Meals preparation List\n");
			printf("Number of students here is %d\n",student_iter);
			printf("Number of Breakfast And Lunch : %d\n",breakAndlunch);
			printf("Number of Dinner : %d\n",dinner);
			break;
		case 15:
			printf("\nWelcome to the Complaints forum\n");
			FILE* pt;
			char ch;
			int x=0;
			pt = fopen("Complaint_form.txt","r");
			if(pt == NULL){
				printf("File not Opened\n");
			}
			else{
				while ( 1 )  
				{  
					ch = fgetc ( pt ) ;  
					if ( ch == EOF )  
					break ;  
					printf("%c",ch) ;x=1;  
				}  
			}
			fclose(pt);
			if(x==0){
				printf("\nNo complaints received\n");
			}
			printf("\n");
			break;
		case 16:
			main();
			break;
		default:
			printf("\nEnter Correct Choice!!!\n");
			break;
	}
	return staff_work();
}

int Admin_Login(){
	char admin[30],admin_pass[20];
	int choice;
	printf("\nHello There Admin\n");
	printf("Enter your admin email : ");
	scanf("%s",admin);
	printf("Enter Password : ");
	scanf("%s",admin_pass);
	int x = check_adminLogin(admin,admin_pass);
	if(x)
	{
		printf("Login Was SuccessFull..\n");
		printf("1. create staff admin\t 2. log out\n");
		printf("Enter choice : ");
		scanf("%d",&choice);
		switch(choice){
			case 1:  // admin is the only person to add staff members
				staff_iter++;
				printf("\nEnter Staff name : ");
				scanf("%s",staff[staff_iter].staff_name);
				printf("Enter email of the staff : ");
				scanf("%s",staff[staff_iter].staff_email);
				printf("Enter Password : ");
				scanf("%s",staff[staff_iter].staff_password);
				printf("Enter Domain of the staff : ");
				scanf("%s",staff[staff_iter].staff_domain);
				printf("Enter Staff ID no : ");
				scanf("%d",&staff[staff_iter].staff_id_no);
				printf("Enter Username : ");
				scanf("%s",staff[staff_iter].staff_username);
				FILE *ptr;
				ptr = fopen("staff_login_details.txt","a+");
				if(ptr == NULL){
					printf("File not opened\n");
				}
				else{
					fprintf(ptr,"%d\n%s\n%d\n",staff[staff_iter].staff_id_no,staff[staff_iter].staff_password,staff_iter);
				}
				fclose(ptr);
				break;
			case 2:
				return 1;
				break;
			default:
				printf("Oops!!! Enter the correct choice");
				break;
		}
	}
	else{
		printf("\n The login id And Password are incorrect");
		Admin_Login();
	}
	return 1;
}

int FAQ()
{
	FILE *fileptr;                           //print the faq questions for the application regarding doubts
	char ch;
	fileptr = fopen("FAQ.txt","r");
	if(fileptr==NULL){
		printf("File not opened");
	}
	else{
		while ( 1 )  
		{  
			ch = fgetc ( fileptr ) ;  
			if ( ch == EOF )  
			break ;  
			printf("%c",ch) ;  
		}  
	}
	fclose (fileptr) ; 
	return 1;
}

int Support()
{
	FILE *fileptr;
	char ch;
	fileptr = fopen("support.txt","r");
	if(fileptr==NULL){
		printf("File not opened");
	}
	else{
		while ( 1 )  
		{  
			ch = fgetc ( fileptr ) ;  
			if ( ch == EOF )  
			break ;  
			printf("%c",ch) ;  
		}  
	}
	fclose (fileptr) ; 
	return 1;
}

