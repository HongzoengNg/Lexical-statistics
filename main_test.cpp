#include<iostream>
#include<string>
#include<fstream>
using namespace std;

bool isLetterNumber(char c)
{
    if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))
        return true;
    else
        return false;
}
bool isOperation(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='='||c=='#'||c=='<'||c=='<='||c=='>'||c=='>='||c==':=')
        return true;
    else
        return false;
}
bool isSperation(char c)
{
    if(c=='('||c==')'||c==','||c==';')
        return true;
    else
        return false;
}
int * findAllSubstr(string str,string p1,string p2,int &nnn)
{
    int *index=new int[20];
    memset(index,0,sizeof(index));
    int k=0;
    int l_str=str.length(),l_p=p1.length();
    for(int i=0;i<l_str-l_p+1;i++){
        string tmpstr=str.substr(i,l_p);
        for(int i=0;i<tmpstr.length();i++){
            if(tmpstr[i]>='a'&&tmpstr[i]<='z'){
                tmpstr[i]+='A'-'a';
            }
        }
        if(tmpstr==p2){
            index[k++]=i;
        }
    }
    nnn=k;
    return index;
}
void calculator(string variance_name[],string upVname[],int variance_num[],int nn,string line)
{
    int f;
    for(int i=0;i<nn;i++){
        int *index;
        int k;
        index=findAllSubstr(line,variance_name[i],upVname[i],k);
        //cout<<k<<endl;
        if(k!=0){
            for(int j=0;j<k;j++){
                if((!isLetterNumber(line[index[j]-1]))&&(!isLetterNumber(line[index[j]+variance_name[i].length()]))){
                    variance_num[i]++;
                    //cout<<variance_name[i]<<":"<<line[index[j]-1]<<" "<<line[index[j]+variance_name[i].length()]<<endl;
                }
            }
        }
    }
}
int main()
{
	ifstream in("input.txt");
	//ofstream fout("output3.txt");
	string line;
	string variance_name[2000];
    string upVname[2000];
    int variance_num[2000];
    int Vnum=0;//变量名个数计数
	memset(variance_num,0,sizeof(variance_num));
	if(in){
	    while(getline(in,line)){
			if((line.find("Const")!=string::npos)||(line.find("Var")!=string::npos)){
                //cout<<line<<endl;
			    int foundSpace=line.find(" ");
			    int startIndex=foundSpace+1;
			    string v="";
			    int i=startIndex;
			    while(i<line.length()){
                    if(line[i]!=','&&line[i]!=';'&&line[i]!='='){
                        v+=line[i];
                    }
                    else if(line[i]=='='){
                        int foundNext=line.find(",",i);
                        if(foundNext==string::npos){
                            foundNext=line.find(";",i);
                        }
                        i=foundNext-1;
                    }
                    else{
                        variance_name[Vnum]=v;
                        string upString=v;
                        for(int x=0;x<upString.length();x++){
                            if(upString[x]>='a'&&upString[x]<='z')
                                upString[x]=upString[x]-'a'+'A';
                        }
                        upVname[Vnum]=upString;
                        variance_num[Vnum++]=1;
                        //cout<<v<<endl;
                        v="";
                    }
                    i++;
			    }
			}
			else{  //非变量代码行
                //cout<<"==="<<endl;
                calculator(variance_name,upVname,variance_num,Vnum,line);
            }
	    }
	}
	else{
		cout<<"no such file"<<endl;
	}
    //cout<<"-----------------------------"<<endl;
	for(int i=0;i<Vnum;i++){
        cout<<variance_name[i]<<":"<<variance_num[i]<<endl;
        //fout<<variance_name[i]<<":"<<variance_num[i]<<endl;
	}
	return 0;
}

