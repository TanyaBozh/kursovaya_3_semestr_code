#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string file_name = "D:\\data\\171123\\x_ray_20kV_PMT550_0dB_coll_2mm\\x_ray_20kV_PMT550_0dB_coll_2mm";
	ostringstream file_name_ost;
	file_name_ost<<file_name<<"\\run_323__ch_38.dat";
	vector<short int> data_tmp;
	
	
	int N_events_per_file=1000;
	int points_per_event=9999;

	int run_size = N_events_per_file * points_per_event;	
	data_tmp.resize(run_size);
	
	FILE *f = NULL;
	cout<<file_name_ost.str()<<endl;
	f = fopen(file_name_ost.str().c_str(), "rb");
	fread(&data_tmp[0], 2, run_size, f);

	cout<<f<<endl;
	return 0;

}