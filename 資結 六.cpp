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
	
	data SetData(char );//���w temp(data �ܼ�) �����e��  
};

struct mystack
{
	data a[MAX] ;
	int top ;
	bool IsEmpty() ;
	bool IsFull() ;
	void Push(data) ;
	data Pop() ;
	data ShowTop();
	Myoppri TopLevel() ;//�� top �� �u���� 
	
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
	void Clear();//initialize
	void PutC(char);//�H�r�� �s�J term 
	void PutN(int);//�H��� �s�J term  
	void inverse();//�N term �˵۩� //super method //�|��e�m���� 
	int  CalcuPost();//�p����  ���p�Ʒ|���h��� 
	myresult()
	{
		Clear();
	}
};

struct PreNum//��Ʀr�H�_�� ��Ū�J���ɭԬO�@�Ӥ@��Ū  
{            
	char data[MAX];//�ثe�����G  
	int       now;
	char PreData; //���eŪ�J���r��
	
	void Put(char);//��J ���� ASCII�� 1~10���Ʀr 
	
	int ReturnData();//�^�ǥثe data �ƭ� (�r������) 
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
	
	char ch;
	mystack s;
	data eatPop; //pop �X�Ӫ��F�� 
	data temp;   //�Ȧs���nŪ�J�� ���(+-*/ & mytype)
	myresult prefix;//�e�m
	myresult post;//��m 
	PreNum pre;  //�O���e�@�� �Ʀr  
		
	while( (ch=fgetc(fptr)) != EOF )//Ū�i�� 
	{
		if( ch == '\n' )
		    printf("  ����");
		printf("%c",ch);//�L�X ���ǥ� 
		
		if( ch != '\n')//�P�@�� 
		{
			if( !IsOperator(ch) )//�O�B�⤸�N�i���P�_  
			{
		        //printf("���� �Ʀr����\n");
				//�x�s���b�o��B�z �ݨ�B��Ť~�B�z) 
		        //printf("%c",ch);
				pre.Put(ch);
			}
			
			else//�B��l �o��~�ݭnPush 
			{
				//-----------------Ū��F�B��l---�`���e��Ū�쪺�Ʀr 
				if( pre.ReturnData()!=0 )//����p��A�� val=0 
				{
					post.PutN  ( pre.ReturnData() );//�s���G
					prefix.PutN( pre.ReturnData() );//++
					
					pre.Clear();
		        }
				//----------------------------------
				if(  IsOperator(ch) )//++
		            prefix.PutC(ch);
				/*���w �u���� �� ���� �Ÿ����e*/
				temp = temp.SetData( ch );//�ǳƦn���(temp) ����s�J stack 
				
				//----------------�ݨ�F �k�A��--------�hpop��ݨ� ���A������ 
				if( ch == ')')//���� push')' 
				{
				   	while( s.a[s.top].oper!='(' )
					{
						eatPop=s.Pop();
					    post.PutC(  eatPop.oper);
		                //printf("%c",eatPop.oper);
					}
					s.Pop();//�A��'('�ᱼ 
				} 
				
				else//-------------push �������O�k�A��--------------------- 
				{
				    if(!s.IsEmpty() && //�O�Ū��N���ΦA�P�_�u�� ����PUSH  
					    (s.TopLevel() > temp.oppri //push �i�h ���u���v���p
					     || temp.oppri == s.TopLevel())//      ���u���v�@��
					  )     
					     //�� pop �A push 
					{  
						//�� pop 
						eatPop=s.Pop();//����  pop���F�� 
		                post.PutC( eatPop.oper );//�񵲪G ��pop �X�Ӫ��F�� 
					 
						//�A push  �J�� '(' �|���u���v
						s.Push(temp); 
					}
					else//����push (������ ��POP || stack ����) 
					{   
					    //Push �� '(' �|���u���v 
						s.Push(temp);	
					} 
				}
			}
			pre.PreData = ch;//�Y�NŪ�J�U�@�Ӧr�� ������e ch
			//printf("�w���� %c\n",ch); 
		}
		
		else//�B�z����(�@�浲��)  
		{
			printf("����   ");
			//-----------------Ū��F(\n)---�`���e��Ū�쪺�Ʀr 
				if( pre.ReturnData()!=0 )//����s�� �A��val=0 
				{
					post.PutN( pre.ReturnData() );//�s���G
					prefix.PutN( pre.ReturnData() );//++
						
					pre.Clear();
				}
			//----------------------------------
			if(  IsOperator(ch) )//++
		            prefix.PutC(ch);
			while( !s.IsEmpty() )
			{
				post.PutC(s.a[s.top].oper);
				s.Pop().oper;  //1,2 �ܤ@�ϥ�
			//	printf("%c",s.Pop().oper);//1,2 �ܤ@�ϥ� 
			}
			/*�L�X���G*/
			post.Show();
			 
		    /*�p�� ��m�B�� �Q�� post �Ȯɦs�񪺤��e */
			printf("\n��e��  ");
			
			prefix.inverse();
			
			printf("���G =>> %d \n",post.CalcuPost());
			prefix.Clear();
			printf("=============================\n");
			
			/*�M�� �Ȧs*/
			post.Clear();
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
	{
	    if( da.oppri == Rpare )// '(' �b stack ���̧C�u���v 
	        da.oppri = low;
		
		a[++top] = da ;
	}
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
data mystack::ShowTop()
{
    return a[top];	
}
//------------------------------------
Myoppri mystack::TopLevel()
{
	if(IsEmpty())
	{
	//	printf("The STACK is empty") ;
	}
	else
		return a[top].oppri;//�^�ǵ��� 
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
void myresult::inverse()
{
	// temp �w�g�ǳƦn �i�H�ϥ�  
	int i=0;
	myresult temp;
	for(i=now-2 ; i>=0 ;i--)//now �O�` ���� ���O��m 
	{
		if( term[i].type==val )
		{
			temp.PutN( term[i].value );
		}
		else
		{
			if( term[i].oper == '(' )
			{
				term[i].oper = ')';
			}
			else if( term[i].oper == ')' )
			{
				term[i].oper = '(';
			}
			temp.PutC( term[i].oper );
			
		} 
	}
	temp.PutC('\n');
	//--------------------------------------------------- 
	mystack s;
	data eat; //pop �X�Ӫ��F�� 
	myresult A;
    char ch,cat;
		
	for( i=0 ; i<temp.now-1 ; i++ )//Ū�i�� 
	{
		eat = temp.term[i];
		if( eat.type == val) 
		{
			A.PutN(eat.value);
		}
		else
		{
			ch = eat.oper;
			eat = eat.SetData( ch );
			
			if( s.IsEmpty() )
			{
				s.Push(eat);
			}
			
			else
			{
				if( ch == ')')
				{
					while( s.ShowTop().oper != '(' )
					{
						cat=s.Pop().oper;
						A.PutC(cat);
					}
					s.Pop(); 
				}
			
				else
				{
			  	  if( eat.oppri < s.ShowTop().oppri )
					{
						cat=s.Pop().oper;
						A.PutC(cat);
						s.Push(eat);
					}
					else
					{
						s.Push(eat);
					}
				}
		    }
		}
	}
	while( !s.IsEmpty() )
	{
		cat=s.Pop().oper;
		A.PutC(cat);
	}
	myresult B;
	B.now = A.now;
	for(i=now-1 ; i>=0 ; i-- )
	{
		if( A.term[i].type == val )
		{
			printf("%d",A.term[i].value);
		}
		else
		{
			if(A.term[i].oper==NULL)
			{
				;
			}
			else
			{
				printf("%c",A.term[i].oper);
            }     
					
		}
	}
	A.Clear(); 
	B.Clear();
	printf("\n");
//--------------------------------------------------- 
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
	//printf("\n");
}
//------------------------------------
void myresult::Clear()
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
int myresult::CalcuPost()
{
	int result = 0;
	int Mae,Ushiro;//pop �X�� ���ǭ�n�|�ۤ� 
	char oper;
	mystack ans;
	data temp;
	
	for(int i = 0 ; i<now ; i++)
	{
		/*if( term[i].type==val )
		    printf("%d",term[i].value);
		else    
		    printf("%c",term[i].oper);
		*/
		if( term[i].type == val)//�Ʀr�N push 
		{
			ans.Push( term[i] );
		}
		
		else//�ݨ�Ÿ� pop pop push 
		{
			switch ( term[i].oper )
			{
				case '+':
					Ushiro = ans.Pop().value;
					Mae    = ans.Pop().value;
					temp.value = Mae + Ushiro;//���n�p�� 
					ans.Push( temp );    //�A push 
					break;
			    case '*':
			    	Ushiro = ans.Pop().value;
					Mae    = ans.Pop().value;
					temp.value = Mae * Ushiro;//���n�p�� 
					ans.Push( temp );    //�A push 
					break;
				case '/'://���Ǫ`�N   
					Ushiro    = ans.Pop().value;
					Mae       = ans.Pop().value;
					temp.value = Mae / Ushiro;//���n�p�� 
					ans.Push( temp );    //�A push 
					break;
				case '-'://���Ǫ`�N 
					Ushiro    = ans.Pop().value;
					Mae       = ans.Pop().value;
					temp.value= Mae - Ushiro;//���n�p�� 
					ans.Push( temp );    //�A push 
					break;
				default: 
				    printf("Not + - / *\n");
			}	
		}
	}
	result = ans.Pop().value;
	//printf("��o���G %d\n",result);
	
	return result;
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
data data::SetData(char ch)
{
	data re;
	switch( ch )
	{
		case '+':
			re.oper='+';
			re.oppri=plus;
			break;
						    
		case '-':
			re.oper='-';
			re.oppri=minus;
			break;
						    
		case '*':
			re.oper='*';
			re.oppri=mult;
		    break;
						    
		case '/':
			re.oper='/';
			re.oppri=divid;
			 break;
						    
		case '(':
			re.oper='(';
			re.oppri=Lpare;
		    break;
						    
		case ')':
			re.oper=')';
			re.oppri=Rpare;
			   break;
		default:
			printf("Not +-*/()\n");
	}
	return re; 
}
//------------------------------------

