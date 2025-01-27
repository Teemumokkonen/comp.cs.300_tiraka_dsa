// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <math.h>
#include <QDebug>
#include <algorithm>
#include <queue>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    int place_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> all_places();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_area_name(AreaID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AreaID> all_areas();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_place(PlaceID id);

    // Estimate of performance:
    // Short rationale for estimate:
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(n);
    // Short rationale for estimate: Iterating over unoredered_map
    // and adding to vector so O(n).
    std::vector<WayID> all_ways();

    // Estimate of performance: O(n)
    // Short rationale for estimate: O(n) is worst case for adding to hashmap
    // but on it is O(1).
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterate over unordered map of ways so worst case O(n).
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: worst case for finding from unordered map is
    // O(n), but on average it is O(1).
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: clear command for hashmap is worst case O(n)
    void clear_ways();

    // Estimate of performance: O(n^3)
    // Short rationale for estimate: This function contains three for while loops nested
    // I implemented here the dijkstras algorithm here so that two function could be
    // done with this funtion only.
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding from
    bool remove_way(WayID id);

    // Estimate of performance: O(n^3)
    // Short rationale for estimate: this function is essentially dijkstras algorithm, but the weight is
    // the amount of crossroads.
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance: -
    // Short rationale for estimate: -
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance: O(n^3)
    // Short rationale for estimate: This funtion uses any_route as it's
    // findind method.
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance: -
    // Short rationale for estimate: -
    Distance trim_ways();

private:
    // Add stuff needed for your class implementation here
    std::unordered_map<AreaID, std::pair<Name, std::vector<Coord>>> areaMap;
    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>> placeMap;
    std::unordered_map<AreaID, std::pair<AreaID, std::unordered_set<AreaID>>> subArea;
    std::unordered_map<WayID, std::vector<Coord>> wayMap;

    // Temp datastructures:
    std::vector<std::pair<WayID, Coord>> tempWays;

};

#endif // DATASTRUCTURES_HH
