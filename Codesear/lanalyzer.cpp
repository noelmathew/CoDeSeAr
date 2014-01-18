//To do:
//Add libmysql.lib in project->properties->linker->input-additional dependancies
//Add include path and library path for mysql files in properties->C/C++ and linker

#include<iostream>
#include<string>
#include<fstream>
//#include <my_global.h>
#include<winsock2.h>//Very important for mysql.h to work
#include<windows.h>

#include<mysql.h>

using namespace std;

void indexer()
{
	MYSQL *connection, *handle=NULL;
	MYSQL_RES *res;
	MYSQL_ROW row, row1;
	const char *sinf=NULL;
	char sql[1024];


	const int linesize = 400;
    char pathKey[14]="In Directory:",pathCheck[15]="", path[linesize],line[linesize],typ[5],*wrd;
    int count=0,i,spaceflag=0, linelength=0, pathlength=0,dummy;
	long indexKey=1001;
    ifstream f2("C:\\Project\\codesear\\Codesear\\t.txt");
    //ofstream f3("C:\\Project\\codesear\\Codesear\\index.txt");
	
//Database connection establishing here	
	handle = mysql_init(NULL);
//connection = mysql_real_connect(&mysql,"host","user","password","database",0,0,0);
	connection = mysql_real_connect(handle,"localhost","root","sear","codesear",0,0,0);
//Read more at Suite101: Using a MySQL Database with C++: How to Access MySQL Stored Functions from a C++ Program http://c-programming.suite101.com/article.cfm/using_a_mysql_databases_with_c#ixzz0cavFOMOM

	while(f2)
    {
		f2.getline(line,linesize);// reading line by line.
		
		linelength=strlen(line);
	
		if(linelength!=0)// Continue only if the line has got some text.
		{
			for(i=0;i<13;i++)
			{
				pathCheck[i]=line[i];
			}
			pathCheck[i]='\0';
	
			if(!(strcmp(pathKey,pathCheck)))//Checks whether line indicates a directory.
			{
				for(i=13;i<linelength;i++)//For copying the line into variable path with only the exact path content
				path[i-13]=line[i];
				path[i-13]='\0';
			}

			else
			{
				line[linelength-6]='\0';// Eliminating [file] from the line to get the proper name of file
				linelength=strlen(line);
				typ[0]=line[linelength-3];// Getting the type of file
				typ[1]=line[linelength-2];
				typ[2]=line[linelength-1];
				typ[3]='\0';
				line[linelength-4]='\0';

			
//INDEXING STARTS HERE				
				{
					
//NORMAL INDEX STARTS HERE

					sprintf(sql,"insert into csindex (name,path,typ) values ('%s','%s','%s');",line,path,typ);// Inserting into the normal index;
					if (!mysql_query(handle,sql)) 
					{ 
						res = mysql_store_result(handle); 
						if (!res) 
						{ 
							mysql_free_result(res); 
						} 
						else 
						{ 
							cout << mysql_error(handle) << endl;
						} 
					} 
					else 
					{ 
						cout << mysql_error(handle) << endl;
					} 

					//f3<<indexKey++<<"\t"<<line<<"\t"<<path<<"\t"<<typ<<endl;// Writing into dummy test file, currently on trial.

		
//INVERTED INDEX STARTS HERE
					char initref[10000], newref[10];// Initref->getting values of existing refernce list.. Newref->New reference that has to be added
					wrd=strtok(line," ,._");
					while(wrd!=NULL)
					{
						sprintf(sql,"select max(id) from csindex;"); //Getting the current file id
						if (!mysql_query(handle,sql)) //QUery execution
						{ 
							res = mysql_store_result(handle); 
							if(res)
							{
								row = mysql_fetch_row(res);
								sprintf(newref,"%s",(char*)row[0]);//Getting the current file id value into newref.
								sprintf(sql,"select ref from csiindex where keyword like '%s';",wrd);//Getting the old reference list 
								mysql_free_result(res);
								if(!mysql_query(handle,sql))
								{
									res=mysql_store_result(handle);
									row1 = mysql_fetch_row(res);  
									if (row1) 
									{ 
										sprintf(initref,"%s",(char*)row1[0]);//Getting the old reference list into initref
										if(!strstr(initref,newref))
										{
											mysql_free_result(res);
											sprintf(sql,"update csiindex set ref = '%s,%s' where keyword like '%s';", initref,newref, wrd);//Adding the new reference to the old refernce list for the keyword, "wrd"
											if(!mysql_query(handle,sql))
											{
												res=mysql_store_result(handle);
												if (!res) 
												{ 
													mysql_free_result(res); 
												} 
												else 
												{ 
													cout << mysql_error(handle) << endl;
												} 
											}
											else 
											{ 
												cout << mysql_error(handle) << endl;
											} 
										}
									}
									else
									{
										sprintf(sql,"insert into csiindex(keyword,ref) values ('%s','%s');", wrd, newref);// If a new keyword, make a new entry into the inverted index table
										mysql_free_result(res);
										if(!mysql_query(handle,sql))
										{
											res=mysql_store_result(handle);
											if(!res)
											{
												mysql_free_result(res);
											}
											else
											{				 
												cout << mysql_error(handle) << endl;
											} 
										}
									}
								}
								else 
								{ 
									cout << mysql_error(handle) << endl;
								} 
							}
							else
							{
								cout << mysql_error(handle) << endl;
							}
						}
						wrd=strtok(NULL," ,._");//Getting the next word from the file name
					}
				}


	
				
			}
		}
	}
	f2.close();
	//f3.close();
	mysql_close(connection);//Closing mysql connection
}

int main()
{	
	DWORD tid;
	HANDLE hThread;
	hThread = CreateThread( NULL,0,(LPTHREAD_START_ROUTINE)indexer,0,0,&tid);
	WaitForSingleObject( hThread, INFINITE );
	CloseHandle( hThread );
	return 0;
}

