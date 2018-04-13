#include <bits/stdc++.h>
using namespace std;

#define pb push_back

// The result of the read is placed in here
// In C++, we use a vector like an array but vectors can dynamically grow
// as required when we get more data.
vector<vector<double> > v;

/*
 * 	This function reads the file whose name is taken as argument
 */ 
void read_from_file(string file_name)
{
	
    fstream file;
	file.open(file_name);
    std::string   line;
    // Read one line at a time into the variable line:
    while(std::getline(file, line))
    {
        std::vector<double>   lineData;
        std::stringstream  lineStream(line);

        double value;
        // Read an data point at a time from the line
        while(lineStream >> value)
        {
            // Add the data points from a line to a 1D array (vector)
            lineData.push_back(value);
        }
        // When all the data points have been read, add the 1D array
        // into a 2D array (as one line in the 2D array)
        v.push_back(lineData);
    }
    cout<<"The dimension of the data set is ";
    cout<<v.size()<<" x ";
    cout<<v[0].size()<<endl;
    /*
    for(int i=0; i<v.size(); i++)
    {
		for(int j=0; j<v[0].size(); j++)
			cout<<v[i][j]<<" ";
		cout<<endl;
    }
    */ 
   // file.close();
}

/*
 * Function to calculate the Euclidean distance between two points  
 */
double euclid_dist(vector<double> x, vector<double> y)
{
	int n = x.size();
	double dist = 0.0;
	for(int i=0; i<n; i++)
	{
		dist += (x[i] - y[i])*(x[i] - y[i]);
	}
	return sqrt(dist);
}

/*
 *  Function to select the initial cluster centers randomly from the given set of points
 */ 
void initialize_cluster_center(vector<vector<double> >&cluster_center, int k)
{
	int m = v.size();
	vector<int> cen;
	for(int i=0; i<k; i++)
		cen.pb(rand()%m);
	for(int i=0; i<k; i++)
		cluster_center[i] = v[cen[i]];
}


/*
 * The main code is implemented in this function 
 */ 
void run_kmeans(vector<vector<double> >&cluster_center, int k)
{
	/*
	 * m - no of rows in input file
	 * n - no of columns in input file
	 */ 
	 
	int m = v.size();
	int n = v[0].size();
	std::vector<std::vector<double> > prev_cluster(k, std::vector<double>(n, 0.0));
	vector<vector<double> > p1(m), p2(m);
	vector<double> x1,x2;
	vector<pair<double, double> > dist_vec(m);
	
	/*
	 * Finding distance of each data point from each cluster center
	 */ 
	
	for(int id=0; id<=100; id++)
	{
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<n; j++)
			{
				x1.pb(v[i][j]);
			}
			double min = INT_MAX; 
			int mini = 0;
			for(int idx=0; idx<k; idx++){
				double dis1 = euclid_dist(cluster_center[idx], x1);
				if(dis1 < min)
				{
					min = dis1;
					mini = idx;
				}
			}
			dist_vec[i] = (make_pair(min, mini));
			x1.clear();
		}
		/*
		 *  Finding the new cluster center and checking if the new
		 *  obtained cluster centers are same as previous then stopping
		 *  the iterations 
		 */ 
		vector<vector<pair<double, int> > > cluster(k,vector<pair<double, int> >(n, make_pair(0.0, 0)));
		for(int i=0; i<m; i++)
		{
			for(int d=0; d<n; d++)
			{
				cluster[dist_vec[i].second][d].first += v[i][d];
				cluster[dist_vec[i].second][d].second += 1;
			}
		}
		for(int i=0; i<k; i++)
		{
			for(int d=0; d<n; d++)
			{
				cluster_center[i][d] = cluster[i][d].first/cluster[i][d].second;
			}
		}
		if(id >= 1)
		{
			bool flag = false;
			for(int d=0; d<n; d++)
			{
				for(int i=0; i<k; i++)
				{
					if(prev_cluster[i][d] != cluster_center[i][d])
						flag = true;
				}
			}
			if(flag == false)
				break;
		}
		for(int d=0; d<n; d++)
			for(int i=0; i<k; i++)
				prev_cluster[i][d] = cluster_center[i][d];
	}
	/*
	 * 	Writing the obtained output to the file named output_file.txt
	 */ 
	ofstream fout("output_file.txt");
	fout<<"The final cluster centers are:\n";
	
	for(int i=0; i<k; i++)
	{
		fout<<"Cluster "<<i+1<<" is\t";
		for(int d=0; d<n; d++)
			fout<<setprecision(6)<<fixed<<cluster_center[i][d]<<" ";
			
		fout<<endl;
	}
	fout.close();
	cout<<"Program ends here\n";
}

int main(int argc, char** argv)
{
	string file_name = argv[1];
	string no_of_cluster = argv[2];
	stringstream ss(no_of_cluster);
    int k = 0;
    ss >> k;
    
    read_from_file(file_name);
    
    vector<vector<double> >cluster_center(k);
    initialize_cluster_center(cluster_center, k);
    run_kmeans(cluster_center, k);
    return 0;
}
