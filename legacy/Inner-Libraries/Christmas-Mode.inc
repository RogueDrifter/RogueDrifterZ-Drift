
#if defined ChristmasMode_included_
    #endinput
#endif

#define ChristmasMode_included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static AddSnowObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:d_stream = 250.0)
{
    new
            object = CreateDynamicObject(modelid, (x + 0.075), (y + 0.15), (z + 0.15), rx, ry, rz, .streamdistance = d_stream);
    for(new a = 0; a < 30; a++)
        SetDynamicObjectMaterial(object, a, 17944, "lngblok_lae2", "white64bumpy");
    return object;
}

static IsPosInRangeOfPoint2D(Float:pos_x, Float:pos_y, Float:range, Float:range_x, Float:range_y)
{
    pos_x -= range_x;
    pos_y -= range_y;
    return ((pos_x * pos_x) + (pos_y * pos_y)) < (range * range);
}

static IsPosInRangeOfPoint3D(Float:pos_x, Float:pos_y, Float:pos_z, Float:range, Float:range_x, Float:range_y, Float:range_z)
{
    pos_x -= range_x;
    pos_y -= range_y;
    pos_z -= range_z;
    return ((pos_x * pos_x) + (pos_y * pos_y) + (pos_z * pos_z)) < (range * range);
}

static IsObjectRemoved(modelid, Float:pos_x, Float:pos_y, Float:pos_z)
{
    if(!GetNumberOfRemovedObjects())
        return false;
    for(new a = 0; a < GetNumberOfRemovedObjects(); a++)
    {
        if(modelid == RemovedObject[a][Model])
        {
            if(IsPosInRangeOfPoint3D(pos_x, pos_y, pos_z, 0.5, RemovedObject[a][Location][0], RemovedObject[a][Location][1], RemovedObject[a][Location][2]))
                return true;
        }
    }
    return false;
}

stock CreateSnowInRange(Float:pos_x, Float:pos_y, Float:range, Float:max_z = 300.0, Float:min_obj_model_size = 30.0)
{
    new
            count;
    for(new a = 0; a < SEARCH_DATA_SIZE; a++)
    {
        if(SearchData[a][SearchZ] > max_z)
            continue;

        if(!IsPosInRangeOfPoint2D(SearchData[a][SearchX], SearchData[a][SearchY], range, pos_x, pos_y))
            continue;
        if(GetColSphereRadius(SearchData[a][Search_Model]) < min_obj_model_size)
            continue;
        if(IsObjectRemoved(SearchData[a][Search_Model], SearchData[a][SearchX], SearchData[a][SearchY], SearchData[a][SearchZ]))
            continue;
        AddSnowObject(
            SearchData[a][Search_Model],
            SearchData[a][SearchX],
            SearchData[a][SearchY],
            SearchData[a][SearchZ],
            SearchData[a][SearchRX],
            SearchData[a][SearchRY],
            SearchData[a][SearchRZ],
            (100.0 + GetColSphereRadius(SearchData[a][Search_Model]))
        );
        count++;
    }
    printf("Total snow objects: %i", count);
    return true;
}