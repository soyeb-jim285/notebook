/**
* Author: Cp algorithms
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns the summation polygon of two polygons.
 * Time: O(n+m)
 * Status:
 */

#pragma once
#include "Point.h" 
void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P); reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]); P.push_back(P[1]);
    Q.push_back(Q[0]); Q.push_back(Q[1]);
    // main part
    vector<pt> ret;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        ret.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        i += cross >= 0 && i < P.size() - 2;
        j += cross <= 0 && j < Q.size() - 2;
    }
    return ret;
}
