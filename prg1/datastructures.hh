// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <unordered_map>
#include <functional>
#include <set>
#include <unordered_set>
#include <math.h>
#include <QDebug>
#include <algorithm>

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

    // Estimate of performance: O(1)
    // Short rationale for estimate: The time for to get size from unordered map is O(1)
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: According to c++ libraries clear function is linear
    // in time complecity
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: This method since for looping unordered map is linear
    // and pushing to vectors last element is constant
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Since finding and inserting are both in worst case linear
    // unordered map the complexity must be O(n) in this function.
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Again findind certain element from unordered map in worst case is
    // linear.
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: same explanation as in get_place_name_type
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: This function could be faster but it has to
    // loop through map so it's linear. Sorting is done in the loop with the set function.
    // this function insert is O(log(n)) because it is red-black tree data structure
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: This function could be faster but it has to
    // loop through map so it's linear. Sorting is done in the loop with the set function.
    // this function insert is O(log(n)) because it is red-black tree data structure
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: this function has for loop which loops through to find all
    // all the places so its time complexity is linear.
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: this function has for loop which loops through to find all
    // all the places so its time complexity is linear.
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Search from the map here again so this function is linear
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Search from the map here again so this function is linear
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: This operation is linear since function has to first check if
    // the value is already in the map and after that it has to insert the given values to the map.
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This operation is also linear since finding element from
    // map is linear in the worst case.
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This operation is also linear since finding element from
    // map is linear in the worst case.
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This method since for looping unordered map is linear
    // and pushing to vectors last element is constant
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n)
    // Short rationale for estimate: This operation is also linear since finding element from
    // map is linear in the worst case.
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function goes through the linked parents of the
    // subareas recursively and returns them in the vector. Time complexity for this is linear.
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations


    void creation_finished();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: This function is essentially same subarea_in_areas,
    // but there is for loop before the recursive call.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: nlog(n)
    // Short rationale for estimate: This one is essentially same as the sorting alpabetically
    // difference is the that from the sorted set only first three values will be given to the
    // vector that is returned
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding from map is linear in the worst case.
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: This one ended to be n^2 because I can't use sorted lists.
    // if I found way to use sorted lists then it would be O(n+m)
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

private:
    // Add stuff needed for your class implementation here
    std::unordered_map<AreaID, std::pair<Name, std::vector<Coord>>> areaMap;
    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>> placeMap;
    std::unordered_map<AreaID, std::pair<AreaID, std::unordered_set<AreaID>>> subArea;


};

#endif // DATASTRUCTURES_HH
