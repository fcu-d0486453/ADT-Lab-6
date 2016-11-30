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
	
	data SetData(char );//給定 temp(data 變數) 的內容用  
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
	Myoppri TopLevel() ;//看 top 的 優先級 
	
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
	void Clear();//initialize
	void PutC(char);//以字元 存入 term 
	void PutN(int);//以整數 存入 term  
	void inverse();//將 term 倒著放 //super method //會把前置完成 
	int  CalcuPost();//計算後序  有小數會失去精準 
	myresult()
	{
		Clear();
	}
};

struct PreNum//把數字黏起來 ∵讀入的時候是一個一個讀  
{            
	char data[MAX];//目前的結果  
	int       now;
	char PreData; //先前讀入的字元
	
	void Put(char);//放入 元素 ASCII為 1~10的數字 
	
	int ReturnData();//回傳目前 data 數值 (字串轉整數) 
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
	
	char ch;
	mystack s;
	data eatPop; //pop 出來的東西 
	data temp;   //暫存欲要讀入的 資料(+-*/ & mytype)
	myresult prefix;//前置
	myresult post;//後置 
	PreNum pre;  //記錄前一個 數字  
		
	while( (ch=fgetc(fptr)) != EOF )//讀進來 
	{
		if( ch == '\n' )
		    printf("  中序");
		printf("%c",ch);//印出 中序用 
		
		if( ch != '\n')//同一行 
		{
			if( !IsOperator(ch) )//是運算元就進此判斷  
			{
		        //printf("此為 數字類型\n");
				//儲存不在這邊處理 看到運算符才處理) 
		        //printf("%c",ch);
				pre.Put(ch);
			}
			
			else//運算子 這邊才需要Push 
			{
				//-----------------讀到了運算子---總結前面讀到的數字 
				if( pre.ReturnData()!=0 )//防止計算括號 val=0 
				{
					post.PutN  ( pre.ReturnData() );//存結果
					prefix.PutN( pre.ReturnData() );//++
					
					pre.Clear();
		        }
				//----------------------------------
				if(  IsOperator(ch) )//++
		            prefix.PutC(ch);
				/*給定 優先級 並 給予 符號內容*/
				temp = temp.SetData( ch );//準備好資料(temp) 等後存入 stack 
				
				//----------------看到了 右括號--------則pop到看到 左括號為止 
				if( ch == ')')//不用 push')' 
				{
				   	while( s.a[s.top].oper!='(' )
					{
						eatPop=s.Pop();
					    post.PutC(  eatPop.oper);
		                //printf("%c",eatPop.oper);
					}
					s.Pop();//再把'('丟掉 
				} 
				
				else//-------------push 的都不是右括號--------------------- 
				{
				    if(!s.IsEmpty() && //是空的就不用再判斷優先 直接PUSH  
					    (s.TopLevel() > temp.oppri //push 進去 的優先權較小
					     || temp.oppri == s.TopLevel())//      或優先權一樣
					  )     
					     //先 pop 再 push 
					{  
						//先 pop 
						eatPop=s.Pop();//接收  pop的東西 
		                post.PutC( eatPop.oper );//放結果 收pop 出來的東西 
					 
						//再 push  遇到 '(' 會降優先權
						s.Push(temp); 
					}
					else//直接push (不須用 先POP || stack 為空) 
					{   
					    //Push 到 '(' 會降優先權 
						s.Push(temp);	
					} 
				}
			}
			pre.PreData = ch;//即將讀入下一個字符 紀錄當前 ch
			//printf("已紀錄 %c\n",ch); 
		}
		
		else//處理結束(一行結束)  
		{
			printf("轉後序   ");
			//-----------------讀到了(\n)---總結前面讀到的數字 
				if( pre.ReturnData()!=0 )//防止存到 括號val=0 
				{
					post.PutN( pre.ReturnData() );//存結果
					prefix.PutN( pre.ReturnData() );//++
						
					pre.Clear();
				}
			//----------------------------------
			if(  IsOperator(ch) )//++
		            prefix.PutC(ch);
			while( !s.IsEmpty() )
			{
				post.PutC(s.a[s.top].oper);
				s.Pop().oper;  //1,2 擇一使用
			//	printf("%c",s.Pop().oper);//1,2 擇一使用 
			}
			/*印出結果*/
			post.Show();
			 
		    /*計算 後置運算 利用 post 暫時存放的內容 */
			printf("\n轉前序  ");
			
			prefix.inverse();
			
			printf("結果 =>> %d \n",post.CalcuPost());
			prefix.Clear();
			printf("=============================\n");
			
			/*清除 暫存*/
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
	    if( da.oppri == Rpare )// '(' 在 stack 為最低優先權 
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
		return a[top].oppri;//回傳等級 
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
	// temp 已經準備好 可以使用  
	int i=0;
	myresult temp;
	for(i=now-2 ; i>=0 ;i--)//now 是總 項數 不是位置 
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
	data eat; //pop 出來的東西 
	myresult A;
    char ch,cat;
		
	for( i=0 ; i<temp.now-1 ; i++ )//讀進來 
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
	int Mae,Ushiro;//pop 出來 順序剛好會相反 
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
		if( term[i].type == val)//數字就 push 
		{
			ans.Push( term[i] );
		}
		
		else//看到符號 pop pop push 
		{
			switch ( term[i].oper )
			{
				case '+':
					Ushiro = ans.Pop().value;
					Mae    = ans.Pop().value;
					temp.value = Mae + Ushiro;//做好計算 
					ans.Push( temp );    //再 push 
					break;
			    case '*':
			    	Ushiro = ans.Pop().value;
					Mae    = ans.Pop().value;
					temp.value = Mae * Ushiro;//做好計算 
					ans.Push( temp );    //再 push 
					break;
				case '/'://順序注意   
					Ushiro    = ans.Pop().value;
					Mae       = ans.Pop().value;
					temp.value = Mae / Ushiro;//做好計算 
					ans.Push( temp );    //再 push 
					break;
				case '-'://順序注意 
					Ushiro    = ans.Pop().value;
					Mae       = ans.Pop().value;
					temp.value= Mae - Ushiro;//做好計算 
					ans.Push( temp );    //再 push 
					break;
				default: 
				    printf("Not + - / *\n");
			}	
		}
	}
	result = ans.Pop().value;
	//printf("獲得結果 %d\n",result);
	
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

