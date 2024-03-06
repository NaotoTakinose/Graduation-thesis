#ifndef __CONF_H__
#define __CONF_H__

/// モデルの選択
/**
 * 以下のうちちょうど1つを必ず有効化すること
 */
#define MODEL1
//#define MODEL2
//#define MODEL3

/// シミュレーションの最大ステップ数
/**
 * 3000step = 300sec
 */
#define MAX_STEP 3000

/// 壁の数
#define NUM_WALL 4

/// 出入り口の数
#define NUM_EXIT 12

/// 空間のX方向のサイズ
#define ROOM_XSIZE 120
/// 空間のY方向のサイズ
#define ROOM_YSIZE 9

/// 出入り口のX方向のサイズ
#define EXIT_XSIZE 20
/// 出入り口のY方向のサイズ
#define EXIT_YSIZE 20

/// エージェント発生率
#define AGENT_INFLOW_RATE 0.5

/// エージェントの大きさ
#define AGENT_SIZE      0.4 // 表示時のサイズ
#define AGENT_BODY_SIZE 0.4
#endif //__CONF_H__
