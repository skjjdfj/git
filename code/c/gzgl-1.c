#include <stdio.h>  /*��׼�������������*/
#include <stdlib.h>  /*��׼������*/
#include <string.h>  /*�ַ���������*/

#define HEADER1 " -----------------------------------------------------------Employer------------------------------------------------------------- \n"
#define HEADER2 "|     number    |     name      |     salary    |     bonus     |   deduction   |    paysalary  |    taxes      |  realsalary   | \n"
#define HEADER3 "|---------------|---------------|---------------|---------------|---------------|---------------|---------------|---------------| \n"
#define FORMAT  "|%-15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n"
#define DATA      per->num,per->name,per->salary,per->bonus,per->deduction,per->paysalary,per->taxes,per->realsalary
#define END     "---------------------------------------------------------------------------------------------------------------------------- ---- \n"
#define N 60
int saveflag=0;  /*�Ƿ���Ҫ���̵ı�־����*/
/*������ְ���йص����ݽṹ*/
typedef struct employee      /*���Ϊemployee*/
{
char num[10];   /*ְ�����*/
char name[15];  /*ְ������*/
float salary;     /*��������*/
float bonus;       /*����*/
float deduction;       /*�ۿ�*/
float paysalary;     /*Ӧ������*/
float taxes;       /*˰��*/
float realsalary;     /*ʵ������*/
}Employer;

void menu()  /*���˵�*/
{
system("clear");   /*����*/
printf("                 The Employee' Salary Management System \n");
printf("     *************************Menu********************************\n");
printf("     *  1 input   record             2 delete record             *\n");
printf("     *  3 search  record             4 modify record             *\n");
printf("     *  5 insert  record             6 count  record             *\n");
printf("     *  7 sort    reord              8 save   record             *\n");
printf("     *  9 display record             0 quit   system             *\n");
printf("     *************************************************************\n");
/*printf()�͸�ʽ��������ı�������Ļ��*/
}
void printheader() /*��ʽ�������ͷ*/
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
void printdata(Employer eminfo) /*��ʽ�������������*/
{
printf("printdata");   
}


void disp(Employer eminfo[],int n)  /*��ʾ����eminfo[]�д洢�ļ�¼������Ϊemployee�ṹ�ж��������*/
{
printf("Disp\n");   
printheader();
for(int j=0;j<n;j++){
printf("|-%15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n",eminfo[j].num,eminfo[j].name,eminfo[j].salary,eminfo[j].bonus,eminfo[j].deduction,eminfo[j].paysalary,eminfo[j].taxes,eminfo[j].realsalary);
}
printf(END);
getchar();
getchar();

}
   
void wrong()  /*�������������Ϣ*/
{
printf("\n\n\n\n\n***********Error:input has wrong! press any key to continue**********\n");
getchar();
}

void nofind()  /*���δ���Ҵ�ְ������Ϣ*/
{
printf("\n=====>Not find this employee record!\n");
}

/*************************************************************
���ã����ڶ�λ�����з���Ҫ��ļ�¼�������ر���ü�¼������Ԫ���±�ֵ
������findmess[]����Ҫ���ҵľ�������; nameornum[]���水ʲô�������в���;
**************************************************************/
int locate(Employer eminfo[],int n,char findmess[],char nameornum[])
{
printf("Locate\n");
if(strcmp(nameornum,"num")==0){
	for(int i=0;i<=n;i++){
	if(strcmp(findmess,eminfo[i].num)==0){
	return i;}
}
}
else if(strcmp(nameornum,"name")==0){
	for(int i=0;i<=n;i++){
	if(strcmp(findmess,eminfo[i].name)==0){
 	printf("%d",i);
	return i;}
}
}
else {printf("Not Found");}
}


/*�����ַ����������г�����֤(����<lens)*/
void stringinput(char *t,int lens,char *notice)
{
   char n[255];
   do{
      printf("%s",notice);  /*��ʾ��ʾ��Ϣ*/
      scanf("%s",n);  /*�����ַ���*/
      if(strlen(n)>lens) printf("\n exceed the required length! \n"); /*���г���У�飬����lensֵ��������*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*��������ַ����������ַ���t��*/

}

/*������ֵ��<����ֵ)*/
float numberinput(char *notice)
{
  float t=0.00;
   do{
      printf("%s",notice);    /*��ʾ��ʾ��Ϣ*/
      scanf("%f",&t);  /*�����繤�ʵ���ֵ�͵�ֵ*/
      if(t<0) printf("\n score must >=0! \n"); /*������ֵУ��*/
   }while(t<0);
   return t;
}


 /*����ְ�����ʼ�¼*/
 int add(Employer eminfo[],int n)
 {char num[10];
 int j=0;
 while(1){
 printf("Add\n");
 stringinput(num,10,"input your number");
 if(strcmp("0",num)==0){break;}
 for(int i=0;i<n;i++){
	if(strcmp(num,eminfo[i].num)==0){
	j=1;
	break;}}
 if(j==1){
 printf("your number are repeating\n");
 break;}
 strcpy(eminfo[n].num,num);
 stringinput(eminfo[n].name,10,"input your name");
 eminfo[n].salary=numberinput("input your salary");
 eminfo[n].bonus=numberinput("input your bonus");
 eminfo[n].deduction=numberinput("input your deduction");
 eminfo[n].paysalary=eminfo[n].salary+eminfo[n].bonus-eminfo[n].deduction;
 eminfo[n].taxes=numberinput("input your taxes");
 eminfo[n].realsalary=eminfo[n].paysalary-eminfo[n].taxes;
 n++;
disp(eminfo,n); 
}	

return n;	
}

/*��ְ����Ż���������ѯ��¼*/
void qur(Employer eminfo[],int n)
{char i[10];
 char j[10];
 int k=0;
 int x=1;
 while(i){
 printf("Qur\n");   
 printf("choose the way to search the record(num or name):");
 scanf("%s",i);
 printf("input who you want to search");
 scanf("%s",j);
 k=locate(eminfo,n,j,i);
 printheader();
 printf("|-%15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n",eminfo[k].num,eminfo[k].name,eminfo[k].salary,eminfo[k].bonus,eminfo[k].deduction,eminfo[k].paysalary,eminfo[k].taxes,eminfo[k].realsalary);
 printf(END);
printf("(if you want to quit,enter 0):");
 scanf("%d",&x);
if(x==0){break;}
}
getchar();
getchar();
}

/*ɾ����¼�����ҵ�����ü�¼������Ԫ�ص��±�ֵ��Ȼ����������ɾ��������Ԫ��*/
int del(Employer eminfo[],int n)
{char i[10];
 char j[10];
 int k=0;
 int x=1;
 int y=0;
 while(1){
 printf("Del\n");
 printf("choose the way to delete the record(num or name):");
 scanf("%s",i);
 printf("which record you want delete:");
 scanf("%s",j);
 k=locate(eminfo,n,j,i);
 for(y=k+1;y<n+1;y++){
	eminfo[y-1]=eminfo[y];
}
// printheader();
// printf("|-%15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n",eminfo[k].num,eminfo[k].name,eminfo[k].salary,eminfo[k].bonus,eminfo[k].deduction,eminfo[k].paysalary,eminfo[k].taxes,eminfo[k].realsalary);
// printf(END);
disp(eminfo,n);
printf("if you want to quit,press 0 ");
scanf("%d",&x);
if(x==0){break;}
}
return n;
}

/*�޸ļ�¼���Ȱ������ְ����Ų�ѯ���ü�¼��Ȼ����ʾ�û��޸ı��֮���ֵ����Ų����޸�*/
void modify(Employer eminfo[],int n)
{char i[10];
 char j[10];
 int k=0;
 int x=1;
 while(1){
 printf("Modify\n");  
 printf("choose the way to insert the record(num or name):");
 scanf("%s",i);
 printf("input the number to modify the record:");
 scanf("%s",j);
 k=locate(eminfo,n,j,i);
 printf("you can modify every data unless number \n");
 stringinput(eminfo[k].name,10,"input your name");
 eminfo[k].salary=numberinput("input your salary");
 eminfo[k].bonus=numberinput("input your bonus");
 eminfo[k].deduction=numberinput("input your deduction");
 eminfo[k].paysalary=eminfo[k].salary+eminfo[k].bonus-eminfo[k].deduction;
 eminfo[k].taxes=numberinput("input your taxes");
 eminfo[k].realsalary=eminfo[k].paysalary-eminfo[k].taxes;
 disp(eminfo,n);
 printf("if you want quit ,press 0");
 scanf("%d",&x);
 if(x==0){break;}


}

}
/*�����¼:��ְ����Ų�ѯ��Ҫ���������Ԫ�ص�λ�ã�Ȼ���ڸñ��֮�����һ��������Ԫ�ء�*/
int insert(Employer eminfo[],int n)
{char i[10];
 char j[10];
 int k=0;
 int x=1;
 int y=0;
 while(1){
 printf("Insert\n");  
 printf("choose the way to insert the record(num or name):");
 scanf("%s",i);
 printf("which record you want insert:");
 scanf("%s",j);
 k=locate(eminfo,n,j,i);
 for(y=n+1;y>=k+1;y--){
        strcpy(eminfo[y].num,eminfo[y-1].num);
	strcpy(eminfo[y].name,eminfo[y-1].name);
	eminfo[y].salary=eminfo[y-1].salary;
	eminfo[y].bonus=eminfo[y-1].bonus;
	eminfo[y].deduction=eminfo[y-1].deduction;
	eminfo[y].paysalary=eminfo[y-1].paysalary;
	eminfo[y].taxes=eminfo[y-1].taxes;
	eminfo[y].realsalary=eminfo[y-1].realsalary;
}

 stringinput(eminfo[k].num,10,"input your number");
 stringinput(eminfo[k].name,10,"input your name");
 eminfo[k].salary=numberinput("input your salary");
 eminfo[k].bonus=numberinput("input your bonus");
 eminfo[k].deduction=numberinput("input your deduction");
 eminfo[k].paysalary=eminfo[k].salary+eminfo[k].bonus-eminfo[k].deduction;
 eminfo[k].taxes=numberinput("input your taxes");
 eminfo[k].realsalary=eminfo[k].paysalary-eminfo[k].taxes;
// printheader();
// printf("|-%15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n",eminfo[k].num,eminfo[k].name,eminfo[k].salary,eminfo[k].bonus,eminfo[k].deduction,eminfo[k].paysalary,eminfo[k].taxes,eminfo[k].realsalary);
// printf(END);
n++;
disp(eminfo ,n);
printf("if you want to quit,press 0 ");
scanf("%d",&x);
if(x==0){break;	}
}
return n;
}

/*ͳ�ƹ�˾��Ա���Ĺ����ڸ��ȼ�������*/
void sta(Employer eminfo[],int n)
{int a=0,b=0,c=0,d=0,e=0,i=0,j=0;
printf("Stastic\n");
for(i=0;i<=n;i++){
  j=eminfo[i].realsalary;
  switch(j/1000){
	case 1:e++;break;
	case 2:d++;break;
	case 3:c++;break;
	case 4:b++;break;
	case 5:a++;break;
	defult:{break;}

}}
printf("1000-2000:%d ",e);
printf("2000-3000:%d ",d);
printf("3000-4000:%d ",c);
printf("4000-5000:%d ",b);
printf("5000-6000:%d ",a);
}

/*����ð������ʵ������İ�ʵ�������ֶεĽ������򣬴Ӹߵ���*/
void sort(Employer eminfo[],int n)
{int i=0;
 int j=0;
 char k[10];
 float x;
 printf("Sort\n");  
 for(i=0;i<n;i++){
	for(j=0;j<n;j++){
	if(eminfo[j].realsalary<eminfo[j+1].realsalary){
	strcpy(k,eminfo[j+1].num);
	strcpy(eminfo[j+1].num,eminfo[j].num);
	strcpy(eminfo[j].num,k);

	strcpy(k,eminfo[j+1].name);
        strcpy(eminfo[j+1].name,eminfo[j].name);
        strcpy(eminfo[j].name,k);

	x=eminfo[j+1].salary;
        eminfo[j+1].salary=eminfo[j].salary;
        eminfo[j].salary=x;
	
	x=eminfo[j+1].bonus;
        eminfo[j+1].bonus=eminfo[j].bonus;
        eminfo[j].bonus=x;

	x=eminfo[j+1].deduction;
        eminfo[j+1].deduction=eminfo[j].deduction;
        eminfo[j].deduction=x;

	x=eminfo[j+1].paysalary;
        eminfo[j+1].paysalary=eminfo[j].paysalary;
        eminfo[j].paysalary=x;

	x=eminfo[j+1].taxes;
        eminfo[j+1].taxes=eminfo[j].taxes;
        eminfo[j].taxes=x;

	x=eminfo[j+1].realsalary;
        eminfo[j+1].realsalary=eminfo[j].realsalary;
        eminfo[j].realsalary=x; 	
}
}
}
disp(eminfo,n);

}
/*���ݴ���,���û�û��ר�Ž��д˲����Ҷ��������޸ģ����˳�ϵͳʱ������ʾ�û�����*/
void save(Employer eminfo[],int n)
{
 printf(" Save\n");  
 FILE *fp;
 int i;
 fp=fopen("./employer.txt","w+");
 for(i=0;i<n;i++){
 fwrite(&eminfo[i],sizeof(Employer),1,fp);
 
}
 fclose(fp);
getchar();
getchar();
}


void main()
{
  Employer eminfomation[N];         /*����Employer�ṹ��*/
  FILE *fp;           /*�ļ�ָ��*/
  char select;         /*����ѡ��������*/
  char ch;            /*����(y,Y,n,N)*/
  int count=0;  /*�����ļ��еļ�¼��������Ԫ�ظ�����*/
  fp=fopen("./employer.txt","a+");
  while(!feof(fp)){
  if(fread(&eminfomation[count],sizeof(Employer),1,fp)==1){
	count++;
}
  
  }
  fclose(fp);
  printf("count is %d",count);
  getchar();
  getchar();
  menu();
  printf("please input option number:");
  while(1){
  scanf("%c",&select);
  if(select>='0'&&select<='9'){
  switch(select){
        case '1':count=add(eminfomation,count);break;
        case '2':count=del(eminfomation,count);break;
        case '3':qur(eminfomation,count);break;
        case '4':modify(eminfomation,count);break;
        case '5':insert(eminfomation,count);break;
        case '6':sta(eminfomation,count);break;
        case '7':sort(eminfomation,count);break;
        case '8':save(eminfomation,count);break;
        case '9':disp(eminfomation,count);break;
	case '0':break;
	default:printf("error");}
  	if(select=='0') {
            break;
    }
  }
 else{printf("error");} 
 printf("\nplease input option number\n");
  }


}
