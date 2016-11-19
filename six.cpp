#include <stdio.h>
#include <stdlib.h>
#define MAX 100
/*�A��  �e��*/
typedef enum {null,op,val} mytype ;
typedef enum {low=0,plus=1,minus=1,mult=2,divid=2,Rpare=17,Lpare=17} Myoppri;
int Myatoi(char );//�r�� ��Ʀr 
bool IsOperator(char );//�P�_�O���O  �B��Ÿ� 

struct data
{
	mytype type ;
	Myoppri  oppri;
	int value ;//�O�Ʀr 
	char oper ;//�O�B��l 
};

struct mystack
{
	data a[MAX] ;
	int top ;
	bool IsEmpty() ;
	bool IsFull() ;
	void Push(data) ;
	data Pop() ;
	data Top() ;
	
	mystack()
	{
		top= -1;		
	}
};

struct myresult//�x�s �ഫ�᪺���G 
{
	data term[MAX];
	int  now;
	
	
	void Show(); 
	void Zero();
	void PutC(char);//�H�r�� �s�J term 
	void PutN(int);//�H��� �s�J term  
	
	myresult()
	{
		Zero();
	}
};

struct PreNum//��Ʀr�H�_�� ��Ū�J���ɭԬO�@�Ӥ@��Ū  
{            
	char data[MAX];//�ثe�����G  
	int  now;
	char PreData; //���eŪ�J���r��
	
	void Put(char);//��J ���� ASCII�� 1~10���Ʀr 
	int ReturnData();
	int Clear();//�N���k�s
	
	PreNum()
	{
		Clear(); //data[] / now /  PreData ��l�� 
	} 
}; 
int main()
{
	FILE *fptr;
	fptr = fopen("1117homework.txt","r");
	if( fptr == NULL )
	    printf("open failed.\n");
	
	int           r=0;
	char ch;
	
	mystack s;
	data eatPop; //pop �X�Ӫ��F�� 
	data temp;   //�Ȧs���nŪ�J�� ���(+-*/ & mytype)
	myresult prefix;//�e�m
	myresult post;//��m 
	PreNum pre;  //�O���e�@�� �Ʀr  
		
	while( (ch=fgetc(fptr)) != EOF )//Ū�i�� 
	{
		
		if( ch != '\n')//�P�@�� 
		{
			//printf("�|������ DATA�O %c\n",ch);
			if( !IsOperator(ch) )//�O�B�⤸�N�i���P�_  
			{
		        //printf("���� �Ʀr����\n");
				//�x�s���b�o��B�z �ݨ�B��Ť~�B�z) 
			    printf("%c",ch);
				pre.Put(ch);
			}
			
			else//�B��l �o��~�ݭnPush 
			{
				//----------------------------------�T�w�F �Ʀr���� 
				if( pre.ReturnData()!=0 )
				{
					post.PutN( pre.ReturnData() );//�s���G
					pre.Clear();
		        }
				//----------------------------------
				//printf("push>%c<�Ÿ�\n",ch);
				/*���w �u���� �� ���� �Ÿ����e*/
					switch( ch )
					{
						case '+':
							temp.oper='+';
							temp.oppri=plus;
							break;
						    
				 		case '-':
				 			temp.oper='-';
							temp.oppri=minus;
							break;
						    
						case '*':
							temp.oper='*';
							temp.oppri=mult;
						    break;
						    
						case '/':
							temp.oper='/';
							temp.oppri=divid;
						    break;
						    
						case '(':
							temp.oper='(';
							temp.oppri=Lpare;
						    break;
						    
						case ')':
							temp.oper=')';
							temp.oppri=Rpare;
							
						    break;
						default:
							printf("Not +-*/()\n");
					} 
				//----------------�ݨ�F �k�A��--------�hpop��ݨ� ���A������ 
				if( ch == ')')//���� push 
				{
				   	while( s.a[s.top].oper!='(' )
					{
						eatPop=s.Pop();
					    post.PutC(  eatPop.oper);
						printf("%c",eatPop.oper);
					}
					s.Pop();//�A�� ( �ᱼ 
				} 
				
				else//-------------push �������O�k�A��--------------------- 
				{
				    if(  s.a[s.top].oppri > temp.oppri     //push �i�h ���u���v���p   
					&& s.top!= -1 )//�� pop �A push 
					{
						//�� pop 
						eatPop=s.Pop();//����  pop���F�� 
						printf("%c",eatPop.oper);//�L�X  
						post.PutC( eatPop.oper );//�񵲪G ��pop �X�Ӫ��F�� 
					 
						//�A push
						s.Push(temp); 
					
						if( ch=='(' )//�p�G�O �A�� push�i�h�H�� �ק��u���v 
							s.a[s.top].oppri=low;
					}
					
					else if( temp.oppri > s.a[s.top].oppri //push �i�h ���u���v���j 
					&& s.top!= -1)//���� pop 
					{//����push 
						s.Push(temp); 
					
						if( ch=='(' )//�p�G�O �A�� push�i�h�H�� �ק��u���v 
						s.a[s.top].oppri=low;
					}
					
					else if( temp.oppri == s.a[s.top].oppri //�p�G�춥�@��  
					&& s.top!= -1)                          //���䪺 �B��l ��pop �Apush�i�h 
					{
					  // �ܼ�	
						eatPop=s.Pop();//����  pop���F�� 
						printf("%c",eatPop.oper);//�L�X  
						post.PutC( eatPop.oper );//�񵲪G ��pop �X�Ӫ��F�� 
					 
						//�A push
						//printf("�A push %c\n",temp.oper);
						s.Push(temp); 
					
						if( ch=='(' )//�p�G�O �A�� push�i�h�H�� �ק��u���v 
							s.a[s.top].oppri=low;
					}
				 
				    else//stack ���� ����push 
					{
						s.Push(temp);	
					
						if( ch=='(' )//�p�G�O �A�� push�i�h�H�� �ק��u���v 
							s.a[s.top].oppri=low;
					} 
			    }
			}
			pre.PreData = ch;//�Y�NŪ�J�U�@�Ӧr�� ������e ch
			//printf("�w���� %c\n",ch); 
		}
		
		else//�B�z����(�@�浲��)  
		{
			//----------------------------------�T�w�F �Ʀr���� 
				if( pre.ReturnData()!=0 )
				{
					post.PutN( pre.ReturnData() );//�s���G
					pre.Clear();
				}
			//----------------------------------
			while( !s.IsEmpty() )
			{
				post.PutC(s.a[s.top].oper);
				printf("%c",s.Pop().oper);
			}
			
			printf("\n\n");
		    printf("�U���G��\n");
		    //post.Show();
		    for(int i = 0 ; i<post.now ;i++)
			{
				if( post.term[i].type==val )
			printf("i=%d %3d type=%d\n",i,post.term[i].value,post.term[i].type);
				else
		    printf("i=%d %3c type=%d\n",i,post.term[i].oper ,post.term[i].type);	
			}
	        printf("\n");
			printf("�W���G��\n\n");
			
			/*�L�X���G*/ 
		    
			/*�p�� ��m�B�� �Q�� post �Ȯɦs�񪺤��e */
			/*~~~~~~~~~~~~~*/
			
			/*�M�� �Ȧs*/
			post.Zero();
		} 
	}
	printf("\n");
	fclose(fptr);  
	system("pause");
    return 0;
}
//------------------------------------
bool mystack::IsEmpty()
{
	if(top == -1)
		return true ;
	else
		return false ;
}
//------------------------------------
bool mystack::IsFull()
{
		if(top == MAX - 1)
			return true ;
		else	
 			return false ;
}
//------------------------------------
void mystack::Push(data da)
{
	if(IsFull())
		printf("The STACK is full") ;
	else
		a[++top] = da ;
}
//------------------------------------	
data mystack::Pop()
{
		if(IsEmpty())
			printf("The STACK is empty") ;
		else
			return a[top--] ;
}
//------------------------------------
data mystack::Top()
{
	if(IsEmpty())
		printf("The STACK is empty") ;
	else
		return a[top] ;//�^�ǵ��c   ����Ǧ^�h�n��  val || oper  
}
//------------------------------------
int Myatoi(char a)
{
	return a-'0';
}
//------------------------------------
bool IsOperator(char a)
{
	if( Myatoi(a)>=0 && Myatoi(a)<=10 )
	    return false;
	else
		return true; 
}
//------------------------------------
void myresult::PutC(char a)
{
		term[now].oper = a;
		term[now].type = op;
		now++;
}
//------------------------------------
void myresult::PutN(int a)
{
		term[now].value = a;
		term[now].type  = val;
		now++;
}
//------------------------------------
void myresult::Show()
{
	for(int i = 0 ; i<now ;i++)
	{
		if( term[i].type==val )
			printf("%d",term[i].value);
		else
		    printf("%c",term[i].oper);	
	}
	printf("\n");
}
//------------------------------------
void myresult::Zero()
{
	int i=0;
	while( i!=MAX-1 )
	{
		term[i].oper =  0;
		term[i].value= -1;
		term[i].type=null;
		i++;
	}
	now=0; 
}
//------------------------------------
int PreNum::ReturnData()
{  
	int r=0;
	
	for( int i=0 ; i<now ; i++ )
		r=r*10+(data[i]-'0');
	
	return r;
}
//------------------------------------
void PreNum::Put(char a)
{
	data[now++] = a;
}
//------------------------------------
int PreNum::Clear()
{
	now=0;
	PreData = -1;
	for(int i=0 ; i<MAX ; i++)
	    data[i]=0; 
}
//------------------------------------
