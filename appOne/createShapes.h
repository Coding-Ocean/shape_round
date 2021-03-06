#pragma once
int createTriangle();
int createPolygon(int numCorners);
int createStar();
int createHeart();
//角が丸まった多角形をつくる
int createRoundPolygon(
    //角数(角になる扇形の数)
    int numCorners,
    //角となる扇型をを分割する数（角の滑らかさ）
    int numDivisions,
    //角となる扇形の半径
    float fanRadius,
    //中心から扇形の要までの距離
    float length
);