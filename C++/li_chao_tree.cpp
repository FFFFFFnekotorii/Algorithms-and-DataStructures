struct linear {
	ll k, b;
	
	linear() {
		k = 0;
		b = INF64;
	}
	
	linear(ll k0, ll b0) {
		k = k0;
		b = b0;
	}
	
	ll operator()(ll x) {
		return k * x + b;
	}
};

template<typename func>
struct li_chao_tree {
	vector<func> tree;
	const func neutral = linear();
	
	void resize(ll n) {
		tree.resize(n << 2);
	}
	
	void insert(ll v, ll l, ll r, func f) {
		ll m = (l + r) / 2;
		bool dominate_l = (f(l) < tree[v](l)), dominate_m = (f(m) < tree[v](m));
		
		if (dominate_m) {
			swap(tree[v], f);
		}
		
		if (r - l == 1) {
			return ;
		}
		if (dominate_l != dominate_m) {
			insert(2 * v + 1, l, m, f);
		} else {
			insert(2 * v + 2, m, r, f);
		}
	}
	
	ll min(ll v, ll l, ll r, ll x) {
		if (r - l == 1) {
			return tree[v](x);
		}
		ll m = (l + r) / 2;
		if (x < m) {
			return min(tree[v](x), min(2 * v + 1, l, m, x));
		} else {
			return min(tree[v](x), min(2 * v + 2, m, r, x));
		}
	}
	
	void insert_segment(ll v, ll l, ll r, ll ql, ll qr, func f) {
		if (qr <= l || r <= ql) {
			return ;
		}
		if (ql <= l && r <= qr) {
			insert(v, l, r, f);
			return ;
		}
		ll m = (l + r) / 2;
		insert_segment(2 * v + 1, l, m, ql, qr, f);
		insert_segment(2 * v + 2, m, r, ql, qr, f);
	}
	
};
