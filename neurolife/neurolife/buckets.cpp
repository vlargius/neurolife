#include "buckets.h"



Buckets::Buckets(const Actor & a, bucket_param_t param) :
	a(a),
	param(param)
{

}

void Buckets::fill() {
	/*for_each(grid.begin(), grid.end(), [](auto & vec) {
		for_each(vec.second.begin(), vec.second.end(), [](const Creature* c) {
			c->is_in_bucket = false;
		});
	});

	grid.clear();

	int x = a.x() - param.bucket_size * param.width / 2;
	int y = a.y() - param.bucket_size * param.height / 2;*/

	//const Field * f = a.get_field();
	//
	//for (auto& m : *f->meal) {
	//	//if inside buckets
	//	if (m.x() >= x && m.x() <= x + param.width*param.bucket_size
	//		&& m.y() >= y && m.y() <= y + param.height*param.bucket_size) {
	//		int i = int((m.x() - x) / param.bucket_size);
	//		int j = int((m.y() - y) / param.bucket_size);
	//		grid[make_pair(i, j)].push_back(&m);
	//		m.is_in_bucket = true;
	//	}
	//}
}
