#include <stdio.h>  /*标准输入输出函数库*/
#include <stdlib.h>  /*标准函数库*/
#include <string.h>  /*字符串函数库*/

#define HEADER1 " -----------------------------------------------------------Employer------------------------------------------------------------- \n"
#define HEADER2 "|     number    |     name      |     salary    |     bonus     |   deduction   |    paysalary  |    taxes      |  realsalary   | \n"
#define HEADER3 "|---------------|---------------|---------------|---------------|---------------|---------------|---------------|---------------| \n"
#define FORMAT  "|%-15s|%-15s|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f|%15.2f| \n"
#define DATA      per->num,per->name,per->salary,per->bonus,per->deduction,per->paysalary,per->taxes,per->realsalary
#define END     "---------------------------------------------------------------------------------------------------------------------------- ---- \n"
#define N 60
int saveflag=0;  /*是否需要存盘的标志变量*/
/*定义与职工有关的数据结构*/
typedef struct employee      /*标记为employee*/
{
char num[10];   /*职工编号*/
char name[15];  /*职工姓名*/
float salary;     /*基本工资*/
float bonus;       /*奖金*/
float deduction;       /*扣款*/
float paysalary;     /*应发工资*/
float taxes;       /*税款*/
float realsalary;     /*实发工资*/
}Employer;

void menu()  /*主菜单*/
{
system("clear");   /*清屏*/
printf("                 The Employee' Salary Management System \n");
printf("     *************************Menu********************************\n");
printf("     *  1 input   record             2 delete record             *\n");
printf("     *  3 search  record             4 modify record             *\n");
printf("     *  5 insert  record             6 count  record             *\n");
printf("     *  7 sort    reord              8 save   record             *\n");
printf("     *  9 display record             0 quit   system             *\n");
printf("     *************************************************************\n");
/*printf()送格式化输出至文本窗口屏幕中*/
}
void printheader() /*格式化输出表头*/
{
  printf(HEADER1);
  printf(HEADER2);
  printf(HEADER3);
}
void printdata(Employer eminfo) /*格式化输出表中数据*/
{
printf("printdata");   
}


void disp(Employer eminfo[],int n)  /*显示数组eminfo[]中存储的记录，内容为employee结构中定义的内容*/
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
   
void wrong()  /*输出按键错误信息*/
{
printf("\n\n\n\n\n***********Error:input has wrong! press any key to continue**********\n");
getchar();
}

void nofind()  /*输出未查找此职工的信息*/
{
printf("\n=====>Not find this employee record!\n");
}

/*************************************************************
作用：用于定位数组中符合要求的记录，并返回保存该记录的数组元素下标值
参数：findmess[]保存要查找的具体内容; nameornum[]保存按什么在数组中查找;
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


/*输入字符串，并进行长度验证(长度<lens)*/
void stringinput(char *t,int lens,char *notice)
{
   char n[255];
   do{
      printf("%s",notice);  /*显示提示信息*/
      scanf("%s",n);  /*输入字符串*/
      if(strlen(n)>lens) printf("\n exceed the required length! \n"); /*进行长度校验，超过lens值重新输入*/
     }while(strlen(n)>lens);
     strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/

}

/*输入数值，<＝数值)*/
float numberinput(char *notice)
{
  float t=0.00;
   do{
      printf("%s",notice);    /*显示提示信息*/
      scanf("%f",&t);  /*输入如工资等数值型的值*/
      if(t<0) printf("\n score must >=0! \n"); /*进行数值校验*/
   }while(t<0);
   return t;
}


 /*增加职工工资记录*/
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

/*按职工编号或姓名，查询记录*/
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

/*删除记录：先找到保存该记录的数组元素的下标值，然后在数组中删除该数组元素*/
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

/*修改记录。先按输入的职工编号查询到该记录，然后提示用户修改编号之外的值，编号不能修改*/
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
/*插入记录:按职工编号查询到要插入的数组元素的位置，然后在该编号之后插入一个新数组元素。*/
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

/*统计公司的员工的工资在各等级的人数*/
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

/*利用冒泡排序法实现数组的按实发工资字段的降序排序，从高到低*/
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
/*数据存盘,若用户没有专门进行此操作且对数据有修改，在退出系统时，会提示用户存盘*/
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
  Employer eminfomation[N];         /*定义Employer结构体*/
  FILE *fp;           /*文件指针*/
  char select;         /*保存选择结果变量*/
  char ch;            /*保存(y,Y,n,N)*/
  int count=0;  /*保存文件中的记录条数（或元素个数）*/
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
