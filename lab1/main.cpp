#include "sort.hpp"
#include <cstdio>

signed main() {
	mystd::vector<mystd::item> a;
	mystd::item cur;
	while (scanf("%s %s\n", cur.key, cur.value) > 0) {
		a.Push_back(cur);
	}
	mystd::Counting_sort(a);
	for (int i = 0; i < a.Size(); i++) {
		printf("%s %s\n", a[i].key, a[i].value);
	}
	return 0;
}