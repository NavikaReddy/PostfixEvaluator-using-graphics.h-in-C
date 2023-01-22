#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<ctype.h>
#include<string.h>
 void postfix(char[]);
 void posteval(char[]);
 void graphicspush(int);
 void graphicspop(int);
 void graphicsans(void);
 void graphicsoperator(char);
 void showtop(int);
 void drawstack(void);
 void push(int);
 int pop(void);
 char infix[100],pofix[100];
 int prec(char);
 char stack[20];
 int stack1[30];
 char ss[100];
 int top=-1,flag=0,flag1=0,cnt=0;
 int x1=205,y1=330,x2=295,y2=345,color=1,color1=15;
void main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"");
 setbkcolor(3);   //background color
 strcpy(ss,"CALCULATOR - POSTFIX EVALUATION USING STACKS");
 gotoxy(20,2); //move to centre
 printf("%s",ss);  //print title
 printf("\n\nEnter expression to be simplified\n");
 scanf("%s",infix);
 printf("Infix-> %s\n\n",infix);
 postfix(infix); //converting infix to postfix
 printf("Postfix expression which calculator converts is-> ");
 printf("%s\n\n",pofix);
 posteval(pofix);  //postfix evaluation
 graphicsans();   //print answer
 getch();
}

void postfix(char infix[])
{
  int i,j,x;
  stack[++top]='(';
  strcat(infix,")");
  for(i=0,j=0;infix[i]!='\0';i++)
  {
    if(infix[i]=='(')
    {
     stack[++top]=infix[i];
    }
    else if(isdigit(infix[i]))
    {
      pofix[j]=infix[i];
      j++;
    }
    else if(infix[i]==')')
    {
      while(stack[top]!='(')
      {
	pofix[j]=stack[top--];
	j++;
      }
	 x=stack[top--];
    }
    else
    {
	while(prec(stack[top])>=prec(infix[i]))
	{
	  pofix[j]=stack[top--];
	  j++;
	}
	stack[++top]=infix[i];
    }
  }
  pofix[j]='\0';
 }

 int prec(char c)
 {
   switch(c)
   {
    case '^':return 5;
    case '*':
    case '%':
    case '/':return 4;
    case '+':
    case '-':return 3;
    case '(':return 0;
   }
   return -1;
 }

 void posteval(char pofix[])
 {
  int i,op1,op2;
  drawstack();
  for(i=0;pofix[i]!='\0';i++)
  {
    if(isdigit(pofix[i]))
    {
     flag=0;
     push(pofix[i]-'0');
    }
    else
    {
      graphicsoperator(pofix[i]);
      flag1=0;
      op2=pop();
      flag1=1;
      op1=pop();
      flag=1;
      color=color+2;
      color1=color1-2;
      if(color==3)
	color++;
      if(color==color1 || color1==3)
	color1--;
      switch(pofix[i])
      {
       case '*':push(op1*op2);
		break;
       case '/':push(op1/op2);
		break;
       case '+':push(op1+op2);
		break;
       case '-':push(op1-op2);
		break;
      }
    }
  }
 }

 void push(int x)
 {
   stack1[++top]=x;
   graphicspush(x);
 }

 int pop(void)
 {
  graphicspop(stack1[top]);
  return(stack1[top--]);
 }

 void drawstack (void)
 {
  line(200,150,200,350);
  line(200,350,300,350);
  line(300,350,300,150);
  gotoxy(29,25);
  printf("STACK");
 }

 void graphicspush(int x)
 {
   int a,b,c,d,cnt=0,i,col;
   if(flag==0)
   {

     col=color1;
     for(i=1;i<=2;i++)
     {
      setcolor(col);
      sprintf(ss,"DIGIT SCANNED");
      outtextxy(10,180,ss);
      sprintf(ss,"%d",x);
      outtextxy(45,200,ss);
      if(col!=3)
      sleep(1);
      col=3;
    }
	a=50,b=200,c=140,d=215;
	if(cnt==0)
	{
	setfillstyle(SOLID_FILL,color);
	bar(a,b,c,d);
	setcolor(color1);
	outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
	sleep(1);
	setfillstyle(SOLID_FILL,3);
	bar(a,b,c,d);
	 cnt=1;
	}
    }
    else
    {
       a=540,b=200,c=630,d=215;
	sprintf(ss,"%d",x);
	if(cnt==0)
	{
	setfillstyle(SOLID_FILL,color);
	bar(a,b,c,d);
	setcolor(color1);
	outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
	sleep(1);
	setfillstyle(SOLID_FILL,3);
	bar(c-230,b,a-115,d);//to clear symbol and =
	bar(c-115,b,a,d);
	a=a-230;
	c=c-230;
	sprintf(ss,"OPERAND-1");
	setcolor(3);
	for(i=1;i<=3;i++)
	{
	 sleep(1);
	 bar(a,b,c,d);
	 outtextxy(((a+c)/2)-33,((b+d)/2)-20,ss);
	 a=a+115;
	 c=c+115;
	 sprintf(ss,"OPERAND-2");
	}
	 cnt=1;
	}
		sprintf(ss,"%d",x);
    }
       if(cnt==1)
	{
	 a=205;
	 b=150;
	 c=295;
	 d=165;
	 setfillstyle(SOLID_FILL,color);
	 bar(a,b,c,d);
	setcolor(color1);
	outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
	sleep(1);
	 setfillstyle(SOLID_FILL,3);
	 bar(a,b,c,d);
	 cnt=2;
	}
	if(cnt==2)
	{
	 setfillstyle(SOLID_FILL,color);
	 bar(x1,y1,x2,y2);
	 setcolor(color1);
	 outtextxy(((x1+x2)/2)-10,((y1+y2)/2)-2,ss);
	 showtop(0);
	 cnt=3;
	}
     y1=y1-15;
     y2=y2-15;
     if(color<15)
     color++;
     else
     color=1;
     if(color==3)
     color++;
     if(color1>0)
     color1--;
     else
     color1=15;
     if(color1==color || color1==3)
     color1--;
 }

 void showtop(int key)
 {
	    sprintf(ss,"top->");
	   if(cnt==0)
	   {
	    setcolor(15);
	    outtextxy(x1-50,y1,ss);
	    cnt++;
	   }
	   else
	   {

	    if(key==1)
	    {
	    setcolor(3);
	     outtextxy(x1-50,y1,ss);
	    setcolor(15);
	    outtextxy(x1-50,y1+15,ss);
	    }
	    else
	    {
	      setcolor(3);
	      outtextxy(x1-50,y1+15,ss);
	      setcolor(15);
	      outtextxy(x1-50,y1,ss);
	    }
	   }

 }

 void graphicspop(int x)
 {
   int a,b,c,d;
      color=color-1;
      color1=color1+1;
      if(color==3)
	color--;
      if(color==color1 || color1==3)
	color1--;
   sprintf(ss,"%d",x);
   y1=y1+15;
   y2=y2+15;
   setfillstyle(SOLID_FILL,3);
   bar(x1,y1,x2,y2);
   showtop(1);
   sprintf(ss,"%d",x);
   a=205;
   b=150;
   c=295;
   d=165;
   setfillstyle(SOLID_FILL,color);
   bar(a,b,c,d);
   setcolor(color1);
   outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
   sleep(1);
   setfillstyle(SOLID_FILL,3);
   bar(a,b,c,d);
   if(flag1==0)
   {
	a=425,b=200,c=515,d=215;
	setfillstyle(SOLID_FILL,color);
	bar(a,b,c,d);
	setcolor(color1);
	sprintf(ss,"OPERAND-2");
	outtextxy(((a+c)/2)-33,((b+d)/2)-20,ss);
	sprintf(ss,"%d",x);
	outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
	sleep(1);
   }
   else
   {
	a=310,b=200,c=400,d=215;
	setfillstyle(SOLID_FILL,color);
	bar(a,b,c,d);
	setcolor(color1);
	sprintf(ss,"OPERAND-1");
	outtextxy(((a+c)/2)-33,((b+d)/2)-20,ss);
	sprintf(ss,"%d",x);
	outtextxy(((a+c)/2)-10,((b+d)/2)-2,ss);
	sleep(1);
   }
 }

 void graphicsans(void)
 {
   sprintf(ss,"<-ANSWER");
   setcolor(15);
   outtextxy(305,335,ss);
 }

 void graphicsoperator(char c)
 {
      int i,col=15;

      for(i=1;i<=2;i++)
      {
       setcolor(col);
       sprintf(ss,"OPERATOR SCANNED");
       outtextxy(10,180,ss);
       sprintf(ss,"%c",c);
       outtextxy(60,200,ss);
       if(col==15)
	sleep(1);
       col=3;
      }

      setcolor(15);
      outtextxy(410,207,ss);

      setcolor(15);
      sprintf(ss,"=");
      outtextxy(525,207,ss);
 }
