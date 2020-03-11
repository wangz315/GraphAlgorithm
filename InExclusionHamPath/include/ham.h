#ifndef HAM_H_
#define HAM_H_


#include <string>
#include <unordered_map>
#include <vector>

#define TAGSIZE 256
#define DIRECT 1
#define UNDIRECT 0

#define UNDEFINED 0
#define ZERO 1

using namespace std;

class HAM
{
	private:
		// instance variables
		int n;
		int *matrix;

		// functions
		void create_instance_3();
		void create_instance_4();
		void read_gml(char* fileName, int direct);
		void read_clq(char* fileName);
		void read_adj(char* fileName);
		void read_txt(char* fileName);

		string string_trim(string str);
		int int_to_binary(unsigned int val, int n, char* subset);
		int binary_to_int(int n, char* subset);
		int subset_cmp(char* subset, char* removed);
		int is_superset(vector<int>* set, int superset);
		void set_flags(int numObj, unordered_map<int, int>* flags, char* subset);

		int compute_num_paths(int s, int t, int n, int* matrix);
		int compute_num_paths(int s, int t, int* matrix);
		int compute_num_sub_paths(int s, int t, int length, int* matrix, char* removed);

		int compute_num_paths_enhance(int s, int t, int length, int* matrix);
		int compute_num_paths_enhance_2(int s, int t, int length, int* matrix);

		string compute_hami_path_origin(int s, int t, int length);
		string compute_hami_path(int s, int t, int length);

		
	public:
		// funtions
		HAM(int x);
		HAM(int n, int* matrix);
		HAM(char* fileName, int direct);
		HAM(char* fileName);
		~HAM();
		
		
		int compute_num_paths(int s, int t);
		int compute_num_cycle();

		int compute_num_paths_enhance(int s, int t);
		int compute_num_cycle_enhance();

		int compute_num_paths_enhance_2(int s, int t);
		int compute_num_cycle_enhance_2();

		
		string compute_hami_path(int s, int t);
		string compute_hami_cycle();

		
};


#endif