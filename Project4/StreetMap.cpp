#include "provided.h"
#include "ExpandableHashMap.h"
#include <sstream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

unsigned int hash(const GeoCoord& g)
{
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}

class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;

private:

	ExpandableHashMap<GeoCoord, vector<StreetSegment>>  m_map;
};

StreetMapImpl::StreetMapImpl()
{

}

StreetMapImpl::~StreetMapImpl()
{
}

bool StreetMapImpl::load(string mapFile)
{
	if (mapFile == "")
		return false;

	int i = 0;
	int segsToload = 0;
	while (i < mapFile.size())
	{
		if (segsToload == 0)
		{
			string Steetname;
			while (mapFile[i] != '/n')
			{
				Steetname = Steetname + mapFile[i];
				i++;
			}
			string segNum;
			i++;
			while (mapFile[i]!= '/n')
			{
				segNum = segNum + mapFile[i];
				i++;
			}
			stringstream number(segNum);
			number >> segsToload;
			i++;
		}


	}  // Delete this line and implement this function correctly
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    return false;  // Delete this line and implement this function correctly
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
