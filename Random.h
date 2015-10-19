/**
* @file Random.h
* @brief 乱数生成のヘッダー
* @data 作成日 2015/08/21
* @author 作成者 Naoki Nakagawa
*/

#ifndef _GdkDx9_Random_h_
#define _GdkDx9_Random_h_

#include <random>

/**
* 乱数生成
*/
class Random
{
public:

	/**
	* インスタンスを取得する
	* @return インスタンスを返す
	*/
	static Random& getInstance();

	/**
	* 範囲を指定して乱数を生成(少数版)
	* @param min 最小値
	* @param max 最大値
	* @return 生成した乱数を返す
	*/
	static float FloatRange(float min, float max);

	/**
	* 範囲を指定して乱数を生成(整数版)
	* @param min 最小値
	* @param max 最大値
	* @return 生成した乱数を返す
	*/
	static int IntRange(int min, int max);

private:

	/**
	* デフォルトコンストラクタ
	* newで生成できないようにprivateで宣言する
	*/
	Random();

	/** メルセンヌ・ツイスタ */
	std::mt19937 mt;
};

#endif	// _GdkDx9_Random_h_
