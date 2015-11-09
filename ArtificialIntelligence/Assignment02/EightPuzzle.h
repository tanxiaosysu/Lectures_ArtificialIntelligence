/*
 * Student Number: 13331235
 * Student Name  : Tan Xiao
 * Content       : 8-Puzzle
 * Date          : 2015-11-08
 */

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

typedef std::string state;

class EightPuzzle {
  public:
    EightPuzzle();
    EightPuzzle(const state & s);
    ~EightPuzzle();
    /* 是否完成 */
    bool Finish();
    /* 某个方向是否可移动 */
    bool CanMove(const char &);
    /* 移动 */
    void Move(const char &);
    /* 设置状态 */
    void SetState(const state &);
    /* 获取状态 */
    state GetState();
    /* 获取某状态对应的值 */
    int GetStateValue(const state &);
    /* 最陡爬山 */
    static bool HillClimbingSA(EightPuzzle &, int &);
    /* 首选爬山 */
    static bool HillClimbingFC(EightPuzzle &, int &);
    /* 模拟退火 */
    static bool SimulatedAnnealing(EightPuzzle &, int &);
    /* 重载输出 */
    friend std::ostream &operator<<(std::ostream &, const EightPuzzle &);
  private:
    /* (N * N) - 1 puzzle, 目前为3 */
    static const int _N;
    /* 下标代表行, 值代表列 */
    state _state;
    /* 方向表, u-up, d-down, l-left, r-right */
    static const char _directions[4];
    /* 状态标记：有局部解, 无局部解, 有最终解 */
    enum solutionState { haveLocal, noLocal, success };
    /* 选取最陡 */
    solutionState SelectSteepestState(state &);
    /* 选取随机更优 */
    solutionState SelectFirstState(state &);
    /* 选取退火 */
    solutionState SelectAnnealingState(state &, const int &);
};
