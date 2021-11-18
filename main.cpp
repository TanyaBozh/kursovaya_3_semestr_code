#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <omp.h> 
#include <utility>
#include <fstream>

//root cern
#include "TApplication.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TThread.h"
#include "TObject.h"

using namespace std;

int main()
{
	string file_name = "D:\\data\\171123\\x_ray_10kV_PMT550_0dB_coll_2mm\\x_ray_10kV_PMT550_0dB_coll_2mm";
	ostringstream file_name_ost;
	file_name_ost<<file_name<<"\\run_374__ch_38.dat";
	vector<short int> data_tmp;
	
	int N_events_per_file=1000;
	int points_per_event=9999;

	int run_size = N_events_per_file * points_per_event;	
	data_tmp.resize(run_size);
	
	FILE *f = NULL;
	cout<<file_name_ost.str()<<endl;
	f = fopen(file_name_ost.str().c_str(), "rb");
	fread(&data_tmp[0], 2, run_size, f);

	vector<vector<short int>> data_ev_point;
	
	data_ev_point.resize(N_events_per_file);
	for (int temp_event_id = 0; temp_event_id < N_events_per_file; temp_event_id++)
	{
		data_ev_point[temp_event_id].resize(points_per_event);
	}

	run_size = N_events_per_file * points_per_event;	
	data_tmp.resize(run_size);
	
	for (int temp_event_id = 0; temp_event_id < N_events_per_file; temp_event_id++)
	{
		for (int j = 0; j < points_per_event; j++)
		{
			const int abs_point = j + temp_event_id * points_per_event;
			data_ev_point[temp_event_id][j] = data_tmp[abs_point];
		}
	}
	
	int event_number = 202;
	vector<double> x;
	vector<double> y;
	x.resize(points_per_event);
	y.resize(points_per_event);
	
	double base_line = 0;
	double period = 20000/16;
	int b = 0;
	for(int i = 0; i < period; i++)
	{
		b = b+data_ev_point[event_number][i];
	}
	cout<<b<<endl;
	base_line = b/period;
	cout<<period<<endl;
	cout<<base_line<<endl;

	for(int i = 0; i < points_per_event; i++)
	{
		x[i] = i*16;
		y[i] = -data_ev_point[event_number][i] + base_line;
	}
	
	TGraph *signal = new TGraph(points_per_event, &x[0], &y[0]);
	signal->Draw();
	
	
	ofstream ofs ("test.txt", std::ofstream::out);
	for(int i = 0; i<points_per_event; i++)
	{
		ofs << x[i]<<"\t"<< y[i]<<"\n";
	}
	ofs.close();
	
	fclose(f);
	return 0;


}