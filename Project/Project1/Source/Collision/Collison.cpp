#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Map/Block.h"
#include "../Map/MapManager.h"
#include <math.h>

//矩形と点の当たり判定
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY)
{
    if (pointX >= squarePosX && pointX <= (squarePosX + squareWidth))
    {
        if (pointY >= squarePosY && pointY <= (squarePosY + squareHeight))
        {
            return true;
        }
    }
        return false;
}

bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height)
{
    //矩形A
    float leftA = squareA_PosX;
    float rightA = squareA_PosX + squareA_Width;
    float topA = squareA_PosY;
    float bottomA = squareA_PosY + squareA_Height;

    //矩形B
    float leftB = squareB_PosX;
    float rightB = squareB_PosX + squareB_Width;
    float topB = squareB_PosY;
    float bottomB = squareB_PosY + squareB_Height;

    // 左右の辺がめり込んでいるかチェック
    if (rightA > leftB && leftA < rightB)
    {
        // 上下の片がめり込んでいるかチェック
        if (bottomA > topB && topA < bottomB)
        {
            // 当たっている
            return true;
        }
    }

    return false;
}

bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY)
{
    // 円の中心から点までの距離を計算する
    float distance = sqrtf((pointX - circlePosX) * (pointX - circlePosX) + (pointY - circlePosY) * (pointY - circlePosY));

    // 求めた距離が半径の長さ以下であれば当たっている
    if (distance <= circleRadius)
    {
        return true;
    }

    return false;
}

bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius)
{
    // 円の中心間の距離を計算する
    float distance = sqrtf((circleB_PosX - circleA_PosX) * (circleB_PosX - circleA_PosX) + (circleB_PosY - circleA_PosY) * (circleB_PosY - circleA_PosY));

    // 中心間の距離が2つの円の半径の合計以下であれば当たっている
    if (distance <= (circleA_Radius + circleB_Radius))
    {
        return true;
    }

    return false;
}
