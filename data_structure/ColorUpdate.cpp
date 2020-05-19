template <class T = int>
class ColorUpdate{
public:
	struct Range{
		Range(int l = -1) : l(l){}
		Range(int l, int r, T v) : l(l) , r(r) , v(v) {}
		int l , r;
		T v;
		bool operator<(const Range &rhs) const { return l < rhs.l; }
	};
	vector<Range> upd(int l , int r , T v){
		vector<Range> ans; 
		if(l > r) return ans;
		auto it = ranges.lower_bound(l);
		if(it != ranges.begin()){
			it--;
			if(it->r > l){
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.l, l, cur.v));
				ranges.insert(Range(l, cur.r, cur.v));
			}
		}
		it = ranges.lower_bound(r);
		if(it != ranges.begin()){
			it--;
			if(it->r > r){
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.l, r, cur.v));
				ranges.insert(Range(r, cur.r, cur.v));
			}
		}
		for(it = ranges.lower_bound(l) ; it != ranges.end() && it->l < r ; it++){
			ans.push_back(*it);
		}
		ranges.erase(ranges.lower_bound(l) , ranges.lower_bound(r));
		ranges.insert(Range(l,r,v));
		return ans;
	}
	Range rangeof(int l){
		auto u = ranges.lower_bound(l+1);
		if(u == ranges.begin()){
			return Range();
		}
		return *prev(u);
	}
private:
	set<Range> ranges;  
};
