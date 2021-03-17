// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

int Datastructures::place_count()
{
    int size = placeMap.size();
    return size;
}

void Datastructures::clear_all()
{
    areaMap.clear();
    placeMap.clear();
    subArea.clear();

}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> id_list;
    for(auto it=placeMap.begin(); it != placeMap.end(); it++) {
        id_list.push_back(it->first);
    }
    return id_list;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{

    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        std::tuple<Name, Coord, PlaceType> values {name, xy, type};
        placeMap.insert(make_pair(id, values));
        return true;
    }
    else  {
        return false;
    }

}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{

    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        return {NO_NAME, PlaceType::NO_TYPE};
    }
    else {
        std::tuple<Name, Coord, PlaceType> tuple = it->second;
        std::pair<Name, PlaceType> place = make_pair(std::get<0>(tuple), std::get<2>(tuple));
        return place;

    }
}

Coord Datastructures::get_place_coord(PlaceID id)
{

    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        return NO_COORD;
    }
    else {
        Coord coords = std::get<1>(it->second);
        return coords;
    }

}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{

    std::unordered_map<AreaID,  std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    if(it == areaMap.end()) {
        std::pair<Name, std::vector<Coord>> values = make_pair(name, coords);
        areaMap.insert(make_pair(id, values));
        return true;
    }
    else  {
        return false;
    }
}


Name Datastructures::get_area_name(AreaID id)
{
    std::unordered_map<PlaceID,  std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    if(it == areaMap.end()) {
        return NO_NAME;
    }
    else {
        return it->second.first;
    }
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    // Replace this comment with your implementation
    std::unordered_map<PlaceID,  std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    if(it == areaMap.end()) {
        return {NO_COORD};;
    }
    else {
        return it->second.second;
    }
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::set<std::pair<Name, PlaceID>> names;
    std::vector<PlaceID> vector_names;
    for(auto it=placeMap.begin();it!=placeMap.end();it++) {
        std::pair<Name, PlaceID> pair = std::make_pair(std::get<0>(it->second), it->first);
        names.insert(pair);
    }
    for(auto it=names.begin();it!=names.end();it++) {
       vector_names.push_back(it->second);
    }
    return {vector_names};
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::set<std::tuple<int, int, PlaceID>> coords;
    std::vector<PlaceID> vector_ids;
    for(auto it=placeMap.begin();it!=placeMap.end();it++) {
        Coord coord = std::get<1>(it->second);
        double lenght = sqrt(pow(coord.x, 2) + pow(coord.y, 2));
        int x =  static_cast<int>(lenght);
        std::tuple<int, int, PlaceID> tuple {x, coord.y, it->first};
        coords.insert(tuple);
    }
    for(auto it=coords.begin();it!=coords.end();it++) {
        vector_ids.push_back(std::get<2>(*it));
    }
    return {vector_ids};
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> vector_ids;
    for(auto it=placeMap.begin();it!=placeMap.end();it++) {
        if(std::get<0>(it->second) == name) {
            vector_ids.push_back(it->first);
        }
    }

    return {vector_ids};
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> vector_ids;
    for(auto it=placeMap.begin();it!=placeMap.end();it++) {
        if(std::get<02>(it->second) == type) {
            vector_ids.push_back(it->first);
        }
    }

    return {vector_ids};
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        return false;
    }
    else  {
        std::get<0>(placeMap.find(id)->second) = newname;
        return true;
    }
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        return false;
    }
    else  {
        std::get<1>(placeMap.find(id)->second) = newcoord;
        return true;
    }
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<PlaceID> id_list;
    for(auto it=areaMap.begin(); it != areaMap.end(); it++) {
        id_list.push_back(it->first);
    }
    return id_list;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{

    std::unordered_map<AreaID,  std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    std::unordered_map<AreaID,  std::pair<Name, std::vector<Coord>>>::const_iterator it2 = areaMap.find(parentid);
    if(it == areaMap.end() or it2 == areaMap.end()) {
        // no area which to add subarea or subarea to which add to areas
        return false;
    }
    else  {
        std::unordered_map<AreaID, std::unordered_set<AreaID>>::const_iterator subit = subArea.find(parentid);
        std::unordered_map<AreaID, std::unordered_set<AreaID>>::const_iterator subit2 = subArea.find(id);
        if(subit == subArea.end()) {
            std::unordered_set<AreaID> set;
            set.insert(id);
            std::pair<AreaID, std::unordered_set<AreaID>> pair = std::make_pair(parentid, set);
            subArea.insert(pair);

            if(subit2 == subArea.end()) {
                std::unordered_set<AreaID> set;
                std::pair<AreaID, std::unordered_set<AreaID>> pair = std::make_pair(id, set);
                subArea.insert(pair);
            }
            return true;
        }
        else {
            subArea[parentid].insert(id);
            if(subit2 == subArea.end()) {
                std::unordered_set<AreaID> set;
                std::pair<AreaID, std::unordered_set<AreaID>> pair = std::make_pair(id, set);
                subArea.insert(pair);
            }
            return true;
        }

    }
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{

    std::vector<PlaceID> id_list;
    std::vector<PlaceID> id_list2;
    std::unordered_map<AreaID, std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    if(it == areaMap.end()) {
        return {NO_AREA};
    }
    for(auto it = subArea.begin(); it != subArea.end(); it++) {
        std::unordered_set<AreaID>::const_iterator id_iter = it->second.find(id);
        if(id_iter != it->second.end()) {
            id_list.push_back(it->first);
        }
    }
    for (unsigned int i = 0; i < id_list.size() ; i++) {
        id_list2 = subarea_in_areas(id_list.at(i));
        id_list.insert(id_list.end(), id_list2.begin(), id_list2.end());
    }
    return id_list;

}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::set<std::tuple<int, int, PlaceID>> loc_close;
    std::vector<PlaceID> places;
    for(auto it=placeMap.begin(); it != placeMap.end(); it++) {
        if(type == PlaceType::NO_TYPE) {
            double dist = sqrt(pow(xy.x - std::get<1>(it->second).x , 2) + pow(xy.y - std::get<1>(it->second).y , 2));
            int x =  static_cast<int>(dist);
            std::tuple<int, int, PlaceID> tuple {x, std::get<1>(it->second).y, it->first};
            loc_close.insert(tuple);

        }
        else if(std::get<2>(it->second) == type){
            double dist = sqrt(pow(xy.x - std::get<1>(it->second).x , 2) + pow(xy.y - std::get<1>(it->second).y , 2));
            int x =  static_cast<int>(dist);
            std::tuple<int, int, PlaceID> tuple {x, std::get<1>(it->second).y, it->first};
            loc_close.insert(tuple);
        }
    }
    int i = 0;
    for(auto it = loc_close.begin(); it != loc_close.end(); it++) {
        if (i < 3) {
        places.push_back(std::get<2>(*it));
        i++;
        }
        else {
            break;
        }

    }
    return {places};
}

bool Datastructures::remove_place(PlaceID id)
{
    std::unordered_map<PlaceID, std::tuple<Name, Coord, PlaceType>>::const_iterator it = placeMap.find(id);
    if(it == placeMap.end()) {
        return false;
    }
    placeMap.erase(it);
    return true;

}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    std::vector<PlaceID> id_list;
    std::vector<PlaceID> id_list2;
    std::unordered_map<AreaID, std::pair<Name, std::vector<Coord>>>::const_iterator it = areaMap.find(id);
    if(it == areaMap.end()) {
        return {NO_AREA};
    }

    std::unordered_map<AreaID, std::unordered_set<AreaID>>::const_iterator iter = subArea.find(id);
    id_list.insert(id_list.end(), iter->second.begin(), iter->second.end());
    for (unsigned int i = 0; i < id_list.size() ; i++) {
        id_list2 = all_subareas_in_area(id_list.at(i));
        id_list.insert(id_list.end(), id_list2.begin(), id_list2.end());
       }

    return id_list;

}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    std::vector<AreaID> areas1;
    std::vector<AreaID> areas2;
    std::vector<AreaID> v3;
    //for intersect function
    std::sort(areas1.begin(), areas1.end());
    std::sort(areas2.begin(), areas2.end());
    areas1 = subarea_in_areas(id1);
    areas2 = subarea_in_areas(id2);
    std::set_intersection(areas1.begin(),areas1.end(),
                          areas2.begin(),areas2.end(),
                          back_inserter(v3));

    if (v3.size() == 0) {
        return NO_AREA;
    }
    else {
        return v3.at(0);
    }
}
