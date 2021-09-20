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


int Judge_1 ( string x, string y )//����һ��������ؼ��ֽ��бȶԣ��Ƿ���1�����Ƿ���0 
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



int Judge_2( char str )//�ж��Ƿ�����ĸ���Ƿ���1�����Ƿ���0 
{
	if( ( str<='z' && str >= 'a' ) || ( str <= 'Z' && str >= 'A' ) )
		return 1;
	else
		return 0;
}



void rank_12(string str)//�����ַ��ȶԣ�����ͳ��Switch-case������ 
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


void rank_34( string str )//if_else������if_elseif_elseǶ�׵ļ���	 
{
	if( Judge_1( str , "else if" ) )//�ȶԱ�else if��Ϊelse if��Ҳ����if 
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
	cout << "�������ļ�·����" << endl;
	cin >> Myfile;
	cout << "�������ѯ�ȼ���" << endl;
	cout << "1--Total�ؼ��ֲ�ѯ" << endl;
	cout << "2--Switch-case��ѯ" << endl;
	cout << "3--If_else��ѯ" << endl;
	cout << "4--IF_elseif_Else��ѯ" << endl;
	cin >> Rank;
	ifstream myfile( Myfile.c_str() );
	int Judge_1( string x,string y );
	int judge_2( char str);
	void rank_12( string str );//�ؼ����ж��Լ�switch-case���� 
	void rank_34( string str );//if_else������if_elseif_elseǶ�׵ļ���	 
	while ( getline( myfile ,temp ))//һ���ж�ȡ 
	{
		istringstream is ( temp );
		string s;
		if( Rank >= 3)
		{
			rank_34( temp );//��Ϊif_elseǶ���пո� 
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
	if( Rank >=3 )
	{
		cout << "If-else num:" << ifelse_num << endl;
	}
	if( Rank >=4 )
	{
		cout << "If-elseif-else num:" <<if_elseif_Else_num;
	}
}
