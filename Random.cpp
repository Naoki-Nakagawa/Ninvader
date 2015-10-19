/**
* @file Random.cpp
* @brief 乱数生成の実装
* @data 作成日 2015/08/21
* @author 作成者 Naoki Nakagawa
*/

#include "Random.h"

using namespace std;

/**
* インスタンスを取得する
* @return インスタンスを返す
*/
Random& Random::getInstance()
{
	static Random instance;
	return instance;
}

/**
* 範囲を指定して乱数を生成(少数版)
* @param min 最小値
* @param max 最大値
* @return 生成した乱数を返す
*/
float Random::FloatRange(float min, float max)
{
	uniform_real_distribution<float> random(min, max);
	return random(getInstance().mt);
}

/**
* 範囲を指定して乱数を生成(整数版)
* @param min 最小値
* @param max 最大値
* @return 生成した乱数を返す
*/
int Random::IntRange(int min, int max)
{
	uniform_int_distribution<int> random(min, max);
	return random(getInstance().mt);
}

/**
* デフォルトコンストラクタ
* newで生成できないようにprivateで宣言する
*/
Random::Random() :
	mt(0)
{
	// シード値を非決定乱数で設定
	random_device seed;
	mt.seed(seed());
}
