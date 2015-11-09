/*
 * Student Number: 13331235
 * Student Name  : Tan Xiao
 * Content       : 8-Queens
 * Date          : 2015-11-08
 */

#include "EightQueens.h"

#include <cmath>
#include <vector>

const int EightQueens::_N = 8;
const std::string EightQueens::_point = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* 构造函数, 初始状态每行一个Queen放到随机列, 行号为下标,列号为对应值 */
EightQueens::EightQueens() {
    _state.resize(_N + 1);
    if (_N <= 8) {
        for (int i = 0; i < _N; i++) {
            _state[i] = _point[rand() % _N];
        }
    }
}

/* 构造函数, 初始状态为给定状态 */
EightQueens::EightQueens(const state & s) {
    _state = s;
}

EightQueens::~EightQueens() {
}

/* 设置状态 */
void EightQueens::SetState(const state & s) {
    _state = s;
}

/* 获取当前状态 */
state EightQueens::GetState() {
    return _state;
}

/* 计算给定状态的h值 */
int EightQueens::GetStateValue(const state & s) {
    int result = 0;
    for (int row = 0; row < _N; row++) {
        /* 按列计算冲突 */
        for (int col = 0; col < _N; col++) {
            if (col == row) {
                continue;
            }
            if (s[col] == s[row]) {
                result++;
            }
        }
        /* 按对角线计算冲突 */
        for (int row2 = 0; row2 < _N; row2++) {
            if (row == row2) {
                continue;
            }
            if (abs(row - row2) == abs(s[row] - s[row2])) {
                result++;
            }
        }
    }
    /* 冲突对数 = 冲突Queen数 / 2 */
    return (result / 2);
}

/* 选择最陡后继状态, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightQueens::solutionState EightQueens::SelectSteepestState(state & s) {
    int min = GetStateValue(_state);

    for (int row = 0; row < _N; row++) {
        state tempS = _state;
        for (int col = 0; col < _N; col++) {
            if (col == row) {
                /* 跳过当前状态 */
                continue;
            }
            tempS[row] = _point[col];
            int tempV = GetStateValue(tempS);
            if (tempV < min) {
                /* 找到更优值则赋值 */
                s = tempS;
                min = tempV;
            }
        }
    }
    /* min=0说明已找到解 */
    if (!min) {
        return success;
    }
    if (min < GetStateValue(_state)) {
        return haveLocal;
    }
    return noLocal;
}

/* 最陡爬山 */
bool EightQueens::HillClimbingSA(EightQueens & eq, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    /* 爬山, current即eq的_state */
    while (temp == haveLocal) {
        temp = eq.SelectSteepestState(neighbor);
        if (neighbor == eq.GetState() || neighbor.empty()) {
            break;
        }
        eq.SetState(neighbor);
        result++;
    }
    /* 判断最终状态是否为解 */
    if (eq.GetStateValue(eq.GetState())) {
        return false;
    }
    return true;
}

/* 选择随机更优后继状态, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightQueens::solutionState EightQueens::SelectFirstState(state & s) {
    std::vector<state> states;
    int currentValue = GetStateValue(_state);
    /* 遍历56个节点找更优 */
    for (int row = 0; row < _N; row++) {
        state tempS = _state;
        for (int col = 0; col < _N; col++) {
            if (col == row) {
                /* 跳过当前状态 */
                continue;
            }
            tempS[row] = _point[col];
            int tempV = GetStateValue(tempS);
            if (tempV < currentValue) {
                /* 找到更优值则push */
                states.push_back(tempS);
            }
        }
    }
    /* 没有更优则无局部解 */
    if (states.empty()) {
        return noLocal;
    }
    /* 在更优节点中随机抽 */
    int randIndex = rand() % states.size();
    int temp = GetStateValue(states[randIndex]);
    s = states[randIndex];
    /* temp=0说明已找到解 */
    if (!temp) {
        return success;
    } else {
        return haveLocal;
    }
    return noLocal;
}

/* 首选爬山 */
bool EightQueens::HillClimbingFC(EightQueens & eq, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    /* 爬山, current即eq的_state */
    while (temp == haveLocal) {
        temp = eq.SelectFirstState(neighbor);
        if (neighbor == eq.GetState() || neighbor.empty()) {
            break;
        }
        eq.SetState(neighbor);
        result++;
    }
    /* 判断最终状态是否为解 */
    if (eq.GetStateValue(eq.GetState())) {
        return false;
    }
    return true;
}

/* 选取退火状态, 参数time代表时间, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightQueens::solutionState EightQueens::SelectAnnealingState(state & s, const int & time) {
    /* T代表温度, 此处温度 - 时间函数为T = 0.99972^time
    理由: 0.99972的50000次方约为0.000001, 因此节点理论上限控制在50000个以内
    节点上限越大, 成功率越高, 时间越慢 */
    double T = pow(0.99972, (time + 0.0));
    /* T近似0的时候终止 */
    if (T <= 0.000001) {
        return noLocal;
    }
    std::vector<state> states;
    int currentValue = GetStateValue(_state);
    /* 遍历56个节点 */
    for (int row = 0; row < _N; row++) {
        state tempS = _state;
        for (int col = 0; col < _N; col++) {
            if (col == row) {
                /* 跳过当前状态 */
                continue;
            }
            tempS[row] = _point[col];
            states.push_back(tempS);
        }
    }
    /* 在全部节点中随机抽 */
    int randIndex = rand() % states.size();
    int targetValue = GetStateValue(states[randIndex]);
    /* 计算deltaE, 由于T始终<1, 为保证概率上限<=1必须使deltaE也<1 */
    double deltaE = (targetValue - currentValue + 0.0)
        / (targetValue>currentValue ? targetValue : currentValue);
    if (deltaE < 0.000001) {
        s = states[randIndex];
        if (targetValue) {
            return haveLocal;
        } else {
            return success;
        }
    } else {
        /* 计算概率 */
        double possibility = rand() / (RAND_MAX + 0.0);
        const double e = 2.718281828;
        double POS_MAX = pow(e, (-1) * (abs(deltaE)) / T);
        /* 随机数成功则选择 */
        if (possibility - POS_MAX <= 0.000001) {
            s = states[randIndex];
            return haveLocal;
        }
    }
    s = _state;
    return haveLocal;
}

/* 模拟退火 */
bool EightQueens::SimulatedAnnealing(EightQueens & eq, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    int time = 0;
    /* 退火, time即时间, 每个循环为一个时间单位 */
    while (temp == haveLocal) {
        temp = eq.SelectAnnealingState(neighbor, time);
        eq.SetState(neighbor);
        result++;
        time++;
    }
    /* 判断最终状态是否为解 */
    if (eq.GetStateValue(eq.GetState())) {
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream & os, const EightQueens & eq) {
    //integer * out = eq.GetEightQueens();
    os << "{ " << eq._state[0];
    for (int i = 1; i < EightQueens::_N; i++) {
        os << ", " << eq._state[i];
    }
    os << " }";
    return os;
}
