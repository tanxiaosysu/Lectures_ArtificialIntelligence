/*
 * Student Number: 13331235
 * Student Name  : Tan Xiao
 * Content       : 8-Queens
 * Date          : 2015-11-08
 */

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

typedef std::string state;

class EightQueens {
  public:
    EightQueens();
    EightQueens(const state & s);
    ~EightQueens();
    /* 设置状态 */
    void SetState(const state &);
    /* 获取状态 */
    state GetState();
    /* 获取某状态对应的值 */
    int GetStateValue(const state &);
    /* 最陡爬山 */
    static bool HillClimbingSA(EightQueens &, int &);
    /* 首选爬山 */
    static bool HillClimbingFC(EightQueens &, int &);
    /* 模拟退火 */
    static bool SimulatedAnnealing(EightQueens &, int &);
    /* 重载输出 */
    friend std::ostream &operator<<(std::ostream &, const EightQueens &);
  private:
    /* N皇后, 目前为8 */
    static const int _N;
    /* 状态数值表 */
    static const std::string _point;
    /* 下标代表行, 值代表列 */
    state _state;
    /* 状态标记：有局部解, 无局部解, 有最终解 */
    enum solutionState { haveLocal, noLocal, success };
    /* 选取最陡 */
    solutionState SelectSteepestState(state &);
    /* 选取随机更优 */
    solutionState SelectFirstState(state &);
    /* 选取退火 */
    solutionState SelectAnnealingState(state &, const int &);
};
