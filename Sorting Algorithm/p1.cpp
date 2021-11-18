#include <iostream>
#include "sort.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class point{
public:
    int x;
    int y;
};

typedef vector<point> set;

int ccw(const point &p1, const point &p2, const point &p3){
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

int dis(const point &p1, const point &p2) {
    return (((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

class angleSort{
public:
    point p0;
    bool operator ()(point &x,point &y) const{
        return((ccw(p0,x,y)>0)||(ccw(p0,x,y)==0&& dis(p0,x)> dis(p0,y)));
    }
};

void getPoint(set &X){
    int pNum;
    cin>>pNum;
    for(int i=0;i<pNum;i++){
        point p{};
        cin>>p.x>>p.y;
        X.push_back(p);
    }
}

void swapPoint(point &p1,point &p2){
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

point get_p0 (set &X) {
    auto p0 = X.begin();
    for (auto it = X.begin() + 1; it != X.end(); ++it) {
        if (it->y < p0->y||(it->y == p0->y&&it->x < p0->x)){
            p0 = it;
        }
    }
    swapPoint(X.front(),*p0);
    for (auto it = X.begin() + 1; it != X.end();) {
        if (it->x == X.front().x && it->y == X.front().y) {
            X.erase(it);
        }
        else it++;
    }
    return X.front();
}



void simplify(point &p0, set &X) {
    int index = 1;
    if((int)X.size()>1){
        if((X[index].x==p0.x)&&(X[index].y==p0.y)){
            X.erase(X.begin()+index);
        }}
    while (index < (int)X.size() - 1) {
        if (ccw(p0, X[index], X[index + 1]))
            index++;
        else {
            if ((X[index].x - p0.x)*(X[index].x - p0.x) < (X[index+1].x - p0.x)*(X[index+1].x - p0.x))
                X.erase(X.begin() + index);
            else
                X.erase(X.begin() + index + 1);
        }
    }
}



void selectConvex(set &X,set &S){
    if ((int)X.size()==0) return ;
    point p0 = get_p0(X);
    angleSort cmp={p0};
    sort(X.begin() + 1, X.end(), cmp);
    simplify(p0,X);
    for (auto & it : X) {
        while (S.size() > 1 && ccw(S[S.size() - 2], S.back(), it) <= 0) {
            S.pop_back();
        }
        S.push_back(it);
    }
}


int main() {
    set X,S;
    getPoint(X);
    selectConvex(X,S);
    for (auto & s : S) {
        cout << s.x << ' ' << s.y << endl;
    }
    return 0;
}