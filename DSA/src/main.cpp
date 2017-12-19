#include "../include/Resource.h"
#include "../include/CRM.h"
#include "../include/MyException.h"
#include "../include/MyUtility.h"
#include "../include/ThreadPool.hpp"
#include "../include/SourcePrepare.h"
#include <thread>
#include <vector>
#include <unistd.h>
using namespace std;

int main()
{
	ThreadPool pool(1);
	SourcePrepare::instance().Recover();
	while(true)
	{
		try
		{
			SourcePrepare::instance().LoadSource();
			vector<future<void>> results;
			while (!SourcePrepare::instance().isSourceEmpty())
			{
				FileInfo fileInfo = SourcePrepare::instance().getSourceInfo();
				results.emplace_back(pool.enqueue(&CRM::Execute,fileInfo));
			}
			for(auto& i: results) i.get();
			usleep(Resource::frame() * 1000);
		}
		catch(exception& e)
		{
			SystemLog::instance()->WriteToFile(e.what());
		}
		catch(...)
		{
			SystemLog::instance()->WriteToFile("Unexpected error occurs....");
		}
	}
}
