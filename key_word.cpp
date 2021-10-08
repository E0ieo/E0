#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

string key_word[32]=
{
		"auto","break","case","char","const","continue","default","double",
		"do","else","enum","extern","float","for","goto","if","int","long",
		"register","return","short","signed","sizeof","static","struct",
		"switch","typedef","union","unsigned","void","volatile","while"
};

vector<int> Case_num;
int switch_num=0;
int case_num=0;
int total_num=0;
int stack[1000]={0};
int ifelse_num=0;
int if_elseif_Else_num=0;
int top=-1;


int Judge_1 ( string x, string y )//Define a function to compare with a keyword. It returns 1 instead of 0 
{
	int Judge_2( char str );
	int position = x.find( y , 0 );
	int len = y.length();	
	if( position != string::npos )
	{
		if( position == 0 ) 
		{
			if(Judge_2( x[position+len] ) == 0 )
			{
				return 1;
			}
			else 
			  	return 0;
		}
		else
		{
			if(Judge_2( x[position+len] ) == 0 && Judge_2( x[position-1] ) ==0 )
			{
				return 1;
			}
			else
				return 0;
		}
	}
	return 0;
}



int Judge_2( char str )//Judge whether it is a letter, return 1, not 0
{
	if( ( str<='z' && str >= 'a' ) || ( str <= 'Z' && str >= 'A' ) )
		return 1;
	else
		return 0;
}



void rank_12(string str)//Compare the core characters and count the number of switch cases 
{
		for(int i = 0; i < 32; i++ )
		{
			if(Judge_1( str , key_word[i] ) == 1)
			{
				if( Judge_1( str , "switch" ) )
				{
					Case_num.push_back( case_num );
					switch_num++;
					case_num = 0;
				}
				if( Judge_1( str , "case" ))
				{
					case_num++;
				}
				total_num++;
				break;
			}
		}
}


void rank_34( string str )//if_ Else count and if_ elseif_ Else nested count	 
{
	if( Judge_1( str , "else if" ) )//Compare else if first, because else if also contains if
	{
		top++;
		stack[top] = 2;
	}	
	else
	{
		if( Judge_1( str , "else" ) )
		{
			 if( stack[top] == 1 )
			 {
			 	ifelse_num++;
			 	top--;
			 }
			 else
			 {
			 	if( stack[top] == 2 )
			 	{
			 		if_elseif_Else_num++;
			 		top--;
				 }
			 }
		}
		else
		{
			if( Judge_1( str ,"if" ) )
			{
				top++;
				stack[top] = 1;
			}
		}
	}
}



int main()
{
	int Rank;
	string Myfile,temp;
	cout << "请输入文件路径：" << endl;
	cin >> Myfile;
	cout << "请输入查询等级：" << endl;
	cout << "1--Total关键字查询" << endl;
	cout << "2--Switch-case查询" << endl;
	cout << "3--If_else查询" << endl;
	cout << "4--IF_elseif_Else查询" << endl;
	cin >> Rank;
	ifstream myfile( Myfile.c_str() );
	int Judge_1( string x,string y );
	int judge_2( char str);
	void rank_12( string str );//Keyword judgment and switch case count
	void rank_34( string str );//if_ Else count and if_ elseif_ Else nested count
	while ( getline( myfile ,temp ))//Read line by line
	{
		istringstream is ( temp );
		string s;
		if( Rank >= 3)
		{
			rank_34( temp );//Because if_ Else nested with spaces 
		}
		while( is >> s ) 
		{
			rank_12( s );
		}
	}
	if( Rank >= 1 ) 
	{
		cout << "Total num:" << total_num << endl;
	}
	if( Rank >= 2 )
	{
		cout << "Switch num:" << switch_num << endl;
		if( !Case_num.empty() )
		{
			Case_num.push_back(case_num);
		}
		else
		{
			Case_num.push_back(0);
		}
		cout << "Case_num :";
		for ( int i = 1; i <= switch_num; i++)
		{
			cout<< Case_num[i] << " ";
		}
		cout << endl;
	}
	if( Rank >= 3 )
	{
		cout << "If-else num:" << ifelse_num << endl;
	}
	if( Rank >= 4 )
	{
		cout << "If-elseif-else num:" <<if_elseif_Else_num;
	}
}
