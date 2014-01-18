#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <E:\Program Files\boost\boost_1_41_0\boost_1_41_0\boost\filesystem\operations.hpp>
#include <E:\Program Files\boost\boost_1_41_0\boost_1_41_0\boost\filesystem\path.hpp>
#include <E:\Program Files\boost\boost_1_41_0\boost_1_41_0\boost\progress.hpp>
#include <iostream>
#include<conio.h>
using namespace std;
namespace bfs= boost::filesystem;

void display( const bfs::path & p)
{
	long int fc=0,dc=0,ec=0,oc=0;

if( bfs::is_directory(p))
{

	cout<<"In Directory:"<< p.directory_string()<<"\n\n";

	bfs::directory_iterator i(p), e;
	

	for(i;i!=e;++i)
	{
		if(bfs::is_directory( i->status()))
		{
			dc++;
			display(*i);
			//cout<< i->path().filename()<<"[directory]\n";
		}
		else if(bfs::is_regular_file(i->status()))
		{
			fc++;
			cout<<i->path().filename()<<"[file]\n";
		}
		else
		{
			oc++;
			cout<<i->path().filename()<<"[others]\n";
		}


	}
	cout<<"File Count:"<<fc<<"\n";
	cout<<"Directory COunt"<<dc<<"\n";
	cout<<"Others Count"<<oc<<"\n";

}
else
{
	cout<<"File Found"<<p.file_string()<<"\n\n";
}


}

int main( int argc, char* argv[])
{
	boost::progress_timer t(cout);
	bfs::path fpath(bfs::initial_path<bfs::path>());
	long int fc=0,dc=0,ec=0,oc=0;

if(argc>1)
fpath= bfs::path(argv[1]); 
else
cout<<"arguments null\n";

if(!bfs::exists(fpath))
{
	cout<<"Not Found\n"<< fpath.file_string();
	
	
}



	display(fpath);
	//getch();
	return 0;


}


/*bool find_file(const bfs::path & dir_path, const string & file_name, bfs::path & pfound)
{
    if( !exists(dir_path) || !is_directory(dir_path) ) 
        return false;
    bfs::directory_iterator iter(dir_path), end_iter;
    for(; iter!= end_iter; ++iter)
    {
        if( bfs::is_directory(*iter) )
        {
            if( find_file(*iter, file_name, pfound) )
                return true;
        }
        else if( iter->leaf() == file_name )
        {
            pfound = *iter;
            return true;
        }
    }
    return false;
}

*/

