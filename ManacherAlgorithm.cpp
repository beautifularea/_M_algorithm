class solution {
public:
	std::string pre_process(std::string& s) {
		int n = s.length();
		if(n==0) return "^$";

		std::string ret = "^";
		for(int i=0;i<n;++i) {
			ret += "#" + s.substr(i,1);
		}

		ret += "#$";

		return ret;
	}

	std::string longest_palindrome(std::string& s) {
		std::string T = pre_process(s);
		const int n = T.length();

		int P[n];
		int C = 0, R = 0;
		for(int i=1;i<n-1;++i) {
			int i_mirror = 2 * C - i;
			P[i] = (R > i) ? std::min(R-i, P[i_mirror]) : 0;

			while(T[i+1+P[i]] == T[i-i-P[i]])
				P[i] ++;

			if(i + P[i] > R) {
				C = i;
				R = i + P[i];
			}
		}

		int max_len = 0;
		int center_index = 0;
		for(int i=1;i<n-1;++i) {
			if(P[i] > max_len) {
				max_len = P[i];
				center_index = i;
			}
		}

		return s.substr((center_index-1-max_len)/2, max_len);
	}
}
