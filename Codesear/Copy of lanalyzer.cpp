#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{	
	const int linesize = 200;
    char pathKey[14]="In Directory:",pathCheck[15]="", path[linesize],line[linesize],typ[5];
    int count=0,i,spaceflag=0, linelength=0, pathlength=0,dummy;
	long indexKey=1001;
    ifstream f2("C:\\Project\\codesear\\Codesear\\t2.txt");
    ofstream f3("C:\\Project\\codesear\\Codesear\\index.txt");
    ofstream f4("C:\\Project\\codesear\\Codesear\\invindex.txt");
    
	while(f2)
    {
		f2.getline(line,linesize);
		
	linelength=strlen(line);
	
	if(linelength!=0)
	{
	for(i=0;i<13;i++)
	{
		pathCheck[i]=line[i];
	}
	pathCheck[i]='\0';
	
	if(!(strcmp(pathKey,pathCheck)))
	{
		for(i=13;i<linelength;i++)
			path[i-13]=line[i];
		path[i-13]='\0';
		
	}

	else
	{
		line[linelength-6]='\0';
		linelength=strlen(line);
		typ[0]=line[linelength-3];
		typ[1]=line[linelength-2];
		typ[2]=line[linelength-1];
		typ[3]='\0';
		f3<<indexKey++<<"\t"<<line<<"\t"<<path<<"\t"<<typ<<endl;
	}
	}
	}
	f2.close();
	f3.close();
	f4.close();
}

	