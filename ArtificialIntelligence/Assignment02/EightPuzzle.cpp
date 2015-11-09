/*
 * Student Number: 13331235
 * Student Name  : Tan Xiao
 * Content       : 8-Puzzle
 * Date          : 2015-11-08
 */

#include "EightPuzzle.h"

#include <cmath>
#include <vector>

const int EightPuzzle::_N = 3;
const char EightPuzzle::_directions[4] = { 'u', 'd', 'l', 'r' };

EightPuzzle::EightPuzzle() {
    _state.resize(_N * _N + 1);
    /* 初状态12345678 */
    _state = "12345678 ";
    /* 随机移动1000次以模拟随机初状态 */
    for (int i = 0; i < 1000; i++) {
        int randIndex = rand() % 4;
        Move(_directions[randIndex]);
    }
}

EightPuzzle::EightPuzzle(const state & s) {
    _state = s;
}

EightPuzzle::~EightPuzzle() {
}

/* 检测是否完成 */
bool EightPuzzle::Finish() {
    return (_state == "12345678 ");
}

/* 能否移动 */
bool EightPuzzle::CanMove(const char & dir) {
    int pos;
    /* 找到空格 */
    for (int i = 0; i < _state.size(); i++) {
        if (_state[i] == ' ') {
            pos = i;
            break;
        }
    }
    switch (dir) {
        case 'u':
            return (pos > 2);
        case 'd':
            return (pos < 6);
        case 'l':
            return (pos % 3);
        case 'r':
            return ((pos % 3) != 2);
        default:
            break;
    }
    return false;
}

/* 移动, 参数为方向表元素 */
void EightPuzzle::Move(const char & dir) {
    if (!CanMove(dir)) {
        return;
    }
    int pos = 0;
    /* 找到空格 */
    for (int i = 0; i < _N * _N; i++) {
        if (_state[i] == ' ') {
            pos = i;
            break;
        }
    }
    switch (dir) {
        case 'u':
            _state[pos] = _state[pos - 3];
            _state[pos - 3] = ' ';
            break;
        case 'd':
            _state[pos] = _state[pos + 3];
            _state[pos + 3] = ' ';
            break;
        case 'l':
            _state[pos] = _state[pos - 1];
            _state[pos - 1] = ' ';
            break;
        case 'r':
            _state[pos] = _state[pos + 1];
            _state[pos + 1] = ' ';
            break;
        default:
            break;
    }
}

/* 设置状态 */
void EightPuzzle::SetState(const state & s) {
    _state = s;
}

/* 获取当前状态 */
state EightPuzzle::GetState() {
    return _state;
}

/* 计算给定状态的h值 */
int EightPuzzle::GetStateValue(const state & s) {
    /* 错误节点数 */
    int wrongNodeCount = 0;
    /* 曼哈顿距离和 */
    int disSum = 0;
    for (int i = 0; i < _N * _N; i++) {
        if (s[i] == ' ') {
            continue;
        }
        int temp = s[i] - '1';
        /* 找到错误节点即求和 */
        if (temp != i) {
            disSum += abs(temp - i) / _N;
            disSum += abs((temp % _N) - (i % _N));
            wrongNodeCount++;
        }
    }
    return disSum;
}

/* 选择最陡后继状态, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightPuzzle::solutionState EightPuzzle::SelectSteepestState(state & s) {
    int min = GetStateValue(_state);

    for (int i = 0; i < 4; i++) {
        if (CanMove(_directions[i])) {
            EightPuzzle tempEP = EightPuzzle(_state);
            tempEP.Move(_directions[i]);
            int tempV = GetStateValue(tempEP.GetState());
            if (tempV < min) {
                /* 找到更优值则赋值 */
                s = tempEP.GetState();
                min = tempV;
            }
        }
    }
    /* 完成则退出 */
    if (Finish()) {
        return success;
    }
    if (min < GetStateValue(_state)) {
        return haveLocal;
    }
    return noLocal;
}

/* 最陡爬山 */
bool EightPuzzle::HillClimbingSA(EightPuzzle & ep, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    /* 爬山, current即eq的_state */
    while (temp == haveLocal) {
        temp = ep.SelectSteepestState(neighbor);
        if (neighbor == ep.GetState() || neighbor.empty()) {
            break;
        }
        ep.SetState(neighbor);
        result++;
    }
    /* 判断最终状态是否为解 */
    if (ep.GetStateValue(ep.GetState())) {
        return false;
    }
    return true;
}

/* 选择随机更优后继状态, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightPuzzle::solutionState EightPuzzle::SelectFirstState(state & s) {
    std::vector<state> states;
    int currentValue = GetStateValue(_state);
    /* 遍历4个节点找更优 */
    for (int i = 0; i < 4; i++) {
        if (CanMove(_directions[i])) {
            EightPuzzle tempEP = EightPuzzle(_state);
            tempEP.Move(_directions[i]);
            int tempV = GetStateValue(tempEP.GetState());
            if (tempV < currentValue) {
                /* 找到更优值则push */
                states.push_back(tempEP.GetState());
            }
        }
    }
    /* 没有更优则无局部解 */
    if (states.empty()) {
        return noLocal;
    }
    /* 在更优节点中随机抽 */
    int randIndex = rand() % states.size();
    s = states[randIndex];
    /* finish说明已找到解 */
    if (Finish()) {
        return success;
    } else {
        return haveLocal;
    }
    return noLocal;
}

/* 首选爬山 */
bool EightPuzzle::HillClimbingFC(EightPuzzle & ep, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    /* 爬山, current即eq的_state */
    while (temp == haveLocal) {
        temp = ep.SelectFirstState(neighbor);
        if (neighbor == ep.GetState() || neighbor.empty()) {
            break;
        }
        ep.SetState(neighbor);
        result++;
    }
    /* 判断最终状态是否为解 */
    if (ep.GetStateValue(ep.GetState())) {
        return false;
    }
    return true;
}

/* 选取退火状态, 参数time代表时间, 返回值代表是否成功选择, 如果成功则s为目标状态 */
EightPuzzle::solutionState EightPuzzle::SelectAnnealingState(state & s, const int & time) {
    /* T代表温度, 此处温度 - 时间函数为T = 0.999908^time
    理由: 0.999908的150000次方约为0.000001, 因此节点理论上限控制在150000个以内
    节点上限越大, 成功率越高, 时间越慢 */
    double T = pow(0.999908, (time + 0.0));
    /* T近似0的时候终止 */
    if (T <= 0.000001) {
        return noLocal;
    }
    std::vector<state> states;
    int currentValue = GetStateValue(_state);
    /* 遍历4个节点 */
    for (int i = 0; i < 4; i++) {
        if (CanMove(_directions[i])) {
            EightPuzzle tempEP = EightPuzzle(_state);
            tempEP.Move(_directions[i]);
            /* 找到则push */
            states.push_back(tempEP.GetState());
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
bool EightPuzzle::SimulatedAnnealing(EightPuzzle & ep, int & result) {
    state neighbor;
    solutionState temp = haveLocal;
    int time = 0;
    /* 退火, time即时间, 每个循环为一个时间单位 */
    while (temp == haveLocal) {
        temp = ep.SelectAnnealingState(neighbor, time);
        ep.SetState(neighbor);
        result++;
        time++;
    }
    /* 判断最终状态是否为解 */
    if (ep.GetStateValue(ep.GetState())) {
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream & os, const EightPuzzle & ep) {
    //integer * out = ep.GetEightPuzzle();
    os << "{ " << ep._state[0];
    for (int i = 1; i < EightPuzzle::_N * EightPuzzle::_N; i++) {
        os << ", " << ep._state[i];
    }
    os << " }";
    return os;
}
