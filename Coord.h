#include <cstdio>
#include <functional>

#include "Vec3.h"

struct Coord
{
	int x;
	int y;

	Coord(int xIn, int yIn);
	Coord(Vec2 pos);
	Coord(Vec3 pos);

	bool operator==(const Coord &other) const
	{
		return (x == other.x && y == other.y);
	}
};

namespace std
{
	template <>
	struct hash<Coord>
	{
		std::size_t operator()(const Coord& k) const
		{
			using std::size_t;
			using std::hash;

			return ((hash<int>()(k.x) 
				^ (hash<int>()(k.y) << 1))
				);
		}
	};
}