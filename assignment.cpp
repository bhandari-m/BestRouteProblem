#include <bits/stdc++.h>
#include <cmath>
using namespace std;

static double haversine(double lat1, double lon1, double lat2, double lon2) {
	// distance between latitudes and longitudes
	double dLat = (lat2 - lat1) * M_PI / 180.0;
	double dLon = (lon2 - lon1) * M_PI / 180.0;

	// convert to radians
	lat1 = (lat1) * M_PI / 180.0;
	lat2 = (lat2) * M_PI / 180.0;

	// apply formulae
	double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
	double rad = 6371;
	double c = 2 * asin(sqrt(a));

	//returns distance between two points in km
	return rad * c;
}

void solve(){
	// All these values can be calculated from Geocoding (Geocoding is the process of converting addresses into geographic coordinates
	double aman_lat, aman_long;
	double r1_lat, r1_long;
	double r2_lat, r2_long;
	double c1_lat, c1_long;
	double c2_lat, c2_long;

	cin>>aman_lat>>aman_long>>r1_lat>>r1_long>>r2_lat>>r2_long>>c1_lat>>c1_long>>c2_lat>>c2_long;
	
	// Calculating distance between all the required points
	double dis_AmanToR1 = haversine(aman_lat, aman_long, r1_lat, r1_long);
	double dis_AmanToR2 = haversine(aman_lat, aman_long, r2_lat, r2_long);
	double dis_R1ToR2 = haversine(r1_lat, r1_long, r2_lat, r2_long);
	double dis_R1ToC1 = haversine(r1_lat, r1_long, c1_lat, c1_long);
	double dis_R1ToC2 = haversine(r1_lat, r1_long, c2_lat, c2_long);
	double dis_R2ToC1 = haversine(r2_lat, r2_long, c1_lat, c1_long);
	double dis_R2ToC2 = haversine(r2_lat, r2_long, r2_lat, r2_long);
	double dis_C1ToC2 = haversine(c1_lat, c1_long, c2_lat, c2_long);

	// Given speed=20km/hr, time (in hr) for travelling each of the distance would be t=d/s
	double t_AmanToR1 = dis_AmanToR1/20;
	double t_AmanToR2 = dis_AmanToR2/20;
	double t_R1ToR2 = dis_R1ToR2/20;
	double t_R1ToC1 = dis_R1ToC1/20;
	double t_R1ToC2 = dis_R1ToC2/20;
	double t_R2ToC1 = dis_R2ToC1/20;
	double t_R2ToC2 = dis_R2ToC2/20;
	double t_C1ToC2 = dis_C1ToC2/20;

	// There will be only 6 paths possible as described in PDF. Calculating time for each of them
	// Average time it takes to prepare a meal is pt1 and pt2 at R1 and R2 respectively
    double pt1, pt2;
    // cin>>pt1>>pt2;
    
	// Case 1 : Aman -> R1 -> C1 -> R2 -> C2
	double T1 = max(pt2, max(t_AmanToR1, pt1) + t_R1ToC1 + t_R2ToC1) + t_R2ToC2;

	// Case 2: Aman -> R1 -> R2 -> C1 -> C2
	double T2 = max(pt2, max(t_AmanToR1, pt1) + t_R1ToR2) + t_R2ToC1 + t_C1ToC2;

	// Case 3: Aman -> R1 -> R2 -> C2 -> C1
	double T3 = max(pt2, max(t_AmanToR1, pt1) + t_R1ToR2) + t_R2ToC2 + t_C1ToC2;

	// Case 4: Aman -> R2 -> C2 -> R1 -> C1
	double T4 = max(pt1, max(t_AmanToR2, pt2) + t_R2ToC2 + t_R1ToC2) + t_R1ToC1;

	// Case 5: Aman -> R2 -> R1 -> C1 -> C2
	double T5 = max(pt1, max(t_AmanToR2, pt2) + t_R1ToR2) + t_R1ToC1 + t_C1ToC2;

	// Case 6: Aman -> R2 -> R1 -> C2 -> C1
	double T6 = max(pt1, max(t_AmanToR2, pt2) + t_R1ToR2) + t_R1ToC2 + t_C1ToC2;

	// mapping each time with the route associated
	map<double,string> route;
	route[T1] = "Aman -> R1 -> C1 -> R2 -> C2";
	route[T2] = "Aman -> R1 -> R2 -> C1 -> C2";
	route[T3] = "Aman -> R1 -> R2 -> C2 -> C1";
	route[T4] = "Aman -> R2 -> C2 -> R1 -> C1";
	route[T5] = "Aman -> R2 -> R1 -> C1 -> C2";
	route[T6] = "Aman -> R2 -> R1 -> C2 -> C1";
	// final_ans is the minimum of all the times calculated from cases above
	double final_times[6] = {T1, T2, T3, T4, T5, T6};
	sort(final_times, final_times+6);
	string final_ans = route[final_times[0]];
	cout<<"Minimum Time Taken is "<<final_times[0]<<endl;
	cout<<"The Route Aman should take is "<<final_ans<<endl;
}

int main(){
	solve();	
	return 0;
}