#include <stdio.h>
#include <stdlib.h>
#define MAX 100
/*括號  前序*/
typedef enum {null,op,val} mytype ;
typedef enum {low=0,plus=1,minus=1,mult=2,divid=2,Rpare=17,Lpare=17} Myoppri;
int Myatoi(char );//字元 轉數字 
bool IsOperator(char );//判斷是不是  運算符號 

struct data
{
	mytype type ;
	Myoppri  oppri;
	int value ;//是數字 
	char oper ;//是運算子 
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

struct myresult//儲存 轉換後的結果 
{
	data term[MAX];
	int  now;
	
	
	void Show(); 
	void Zero();
	void PutC(char);//以字元 存入 term 
	void PutN(int);//以整數 存入 term  
	
	myresult()
	{
		Zero();
	}
};

struct PreNum//把數字黏起來 ∵讀入的時候是一個一個讀  
{            
	char data[MAX];//目前的結果  
	int  now;
	char PreData; //先前讀入的字元
	
	void Put(char);//放入 元素 ASCII為 1~10的數字 
	int ReturnData();
	int Clear();//將此歸零
	
	PreNum()
	{
		Clear(); //data[] / now /  PreData 初始化 
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
	data eatPop; //pop 出來的東西 
	data temp;   //暫存欲要讀入的 資料(+-*/ & mytype)
	myresult prefix;//前置
	myresult post;//後置 
	PreNum pre;  //記錄前一個 數字  
		
	while( (ch=fgetc(fptr)) != EOF )//讀進來 
	{
		
		if( ch != '\n')//同一行 
		{
			//printf("尚未換行 DATA是 %c\n",ch);
			if( !IsOperator(ch) )//是運算元就進此判斷  
			{
		        //printf("此為 數字類型\n");
				//儲存不在這邊處理 看到運算符才處理) 
			    printf("%c",ch);
				pre.Put(ch);
			}
			
			else//運算子 這邊才需要Push 
			{
				//----------------------------------確定了 數字長度 
				if( pre.ReturnData()!=0 )
				{
					post.PutN( pre.ReturnData() );//存結果
					pre.Clear();
		        }
				//----------------------------------
				//printf("push>%c<符號\n",ch);
				/*給定 優先級 並 給予 符號內容*/
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
				//----------------看到了 右括號--------則pop到看到 左括號為止 
				if( ch == ')')//不用 push 
				{
				   	while( s.a[s.top].oper!='(' )
					{
						eatPop=s.Pop();
					    post.PutC(  eatPop.oper);
						printf("%c",eatPop.oper);
					}
					s.Pop();//再把 ( 丟掉 
				} 
				
				else//-------------push 的都不是右括號--------------------- 
				{
				    if(  s.a[s.top].oppri > temp.oppri     //push 進去 的優先權較小   
					&& s.top!= -1 )//先 pop 再 push 
					{
						//先 pop 
						eatPop=s.Pop();//接收  pop的東西 
						printf("%c",eatPop.oper);//印出  
						post.PutC( eatPop.oper );//放結果 收pop 出來的東西 
					 
						//再 push
						s.Push(temp); 
					
						if( ch=='(' )//如果是 括號 push進去以後 修改優先權 
							s.a[s.top].oppri=low;
					}
					
					else if( temp.oppri > s.a[s.top].oppri //push 進去 的優先權較大 
					&& s.top!= -1)//不須 pop 
					{//直接push 
						s.Push(temp); 
					
						if( ch=='(' )//如果是 括號 push進去以後 修改優先權 
						s.a[s.top].oppri=low;
					}
					
					else if( temp.oppri == s.a[s.top].oppri //如果位階一樣  
					&& s.top!= -1)                          //左邊的 運算子 先pop 再push進去 
					{
					  // 變數	
						eatPop=s.Pop();//接收  pop的東西 
						printf("%c",eatPop.oper);//印出  
						post.PutC( eatPop.oper );//放結果 收pop 出來的東西 
					 
						//再 push
						//printf("再 push %c\n",temp.oper);
						s.Push(temp); 
					
						if( ch=='(' )//如果是 括號 push進去以後 修改優先權 
							s.a[s.top].oppri=low;
					}
				 
				    else//stack 為空 直接push 
					{
						s.Push(temp);	
					
						if( ch=='(' )//如果是 括號 push進去以後 修改優先權 
							s.a[s.top].oppri=low;
					} 
			    }
			}
			pre.PreData = ch;//即將讀入下一個字符 紀錄當前 ch
			//printf("已紀錄 %c\n",ch); 
		}
		
		else//處理結束(一行結束)  
		{
			//----------------------------------確定了 數字長度 
				if( pre.ReturnData()!=0 )
				{
					post.PutN( pre.ReturnData() );//存結果
					pre.Clear();
				}
			//----------------------------------
			while( !s.IsEmpty() )
			{
				post.PutC(s.a[s.top].oper);
				printf("%c",s.Pop().oper);
			}
			
			printf("\n\n");
		    printf("下結果為\n");
		    //post.Show();
		    for(int i = 0 ; i<post.now ;i++)
			{
				if( post.term[i].type==val )
			printf("i=%d %3d type=%d\n",i,post.term[i].value,post.term[i].type);
				else
		    printf("i=%d %3c type=%d\n",i,post.term[i].oper ,post.term[i].type);	
			}
	        printf("\n");
			printf("上結果為\n\n");
			
			/*印出結果*/ 
		    
			/*計算 後置運算 利用 post 暫時存放的內容 */
			/*~~~~~~~~~~~~~*/
			
			/*清除 暫存*/
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
		return a[top] ;//回傳結構   之後傳回去要選  val || oper  
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
