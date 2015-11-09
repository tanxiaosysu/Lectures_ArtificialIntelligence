/*
 * Student Number: 13331235
 * Student Name  : Tan Xiao
 * Content       : Main
 * Date          : 2015-11-08
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "EightQueens.h"
#include "EightPuzzle.h"

/* 八皇后测试样例数 */
#define EQ_TEST_COUNT 10000
/* 八数码测试样例数 */
#define EP_TEST_COUNT 100000

void EQ_HillClimbingSA() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    for (int i = 0; i < EQ_TEST_COUNT; i++) {
        int count = 0;
        EightQueens eq;
        bool flag = EightQueens::HillClimbingSA(eq, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 56) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << eq << std::endl;
        */
    }
    average = average * 56 / EQ_TEST_COUNT;
    successRate = ((successCount + 0.0) / EQ_TEST_COUNT) * 100.0;
    std::cout << std::endl << "Hill Climbing Steepest-ascent:" << std::endl;
    std::cout << "Amount of test cases : " << EQ_TEST_COUNT << std::endl
              << "Average search nodes : " << floor(average) << std::endl
              << "Success rate         : " << successRate << "%" << std::endl;
}

void EQ_HillClimbingFC() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    for (int i = 0; i < EQ_TEST_COUNT; i++) {
        int count = 0;
        EightQueens eq;
        bool flag = EightQueens::HillClimbingFC(eq, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 56) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << eq << std::endl;
        */
    }
    average = average * 56 / EQ_TEST_COUNT;
    successRate = ((successCount + 0.0) / EQ_TEST_COUNT) * 100.0;
    std::cout << std::endl << "Hill Climbing First-choice:" << std::endl;
    std::cout << "Amount of test cases : " << EQ_TEST_COUNT << std::endl
              << "Average search nodes : " << floor(average) << std::endl
              << "Success rate         : " << successRate << "%" << std::endl;
}

void EQ_SimulatedAnnealing() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    const int div = 100;
    for (int i = 0; i < (EQ_TEST_COUNT / div); i++) {
        int count = 0;
        EightQueens eq;
        bool flag = EightQueens::SimulatedAnnealing(eq, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 56) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << eq << std::endl;
        */
    }
    average = average / (EQ_TEST_COUNT / div);
    successRate = ((successCount + 0.0) / (EQ_TEST_COUNT / div)) * 100.0;
    std::cout << std::endl << "Simulated Annealing:" << std::endl;
    std::cout << "Amount of test cases  : " << (EQ_TEST_COUNT / div) << std::endl
              << "Average search states : " << floor(average) << std::endl
              << "Success rate          : " << successRate << "%" << std::endl;
}

void EP_HillClimbingSA() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    for (int i = 0; i < EP_TEST_COUNT; i++) {
        int count = 0;
        EightPuzzle ep;
        bool flag = EightPuzzle::HillClimbingSA(ep, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 4) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << EP << std::endl;
        */
    }
    average = average * 4 / EP_TEST_COUNT;
    successRate = ((successCount + 0.0) / EP_TEST_COUNT) * 100.0;
    std::cout << std::endl << "Hill Climbing Steepest-ascent:" << std::endl;
    std::cout << "Amount of test cases : " << EP_TEST_COUNT << std::endl
        << "Average search nodes : " << floor(average) << std::endl
        << "Success rate         : " << successRate << "%" << std::endl;
}

void EP_HillClimbingFC() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    for (int i = 0; i < EP_TEST_COUNT; i++) {
        int count = 0;
        EightPuzzle ep;
        bool flag = EightPuzzle::HillClimbingFC(ep, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 4) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << EP << std::endl;
        */
    }
    average = average * 4 / EP_TEST_COUNT;
    successRate = ((successCount + 0.0) / EP_TEST_COUNT) * 100.0;
    std::cout << std::endl << "Hill Climbing First-choice:" << std::endl;
    std::cout << "Amount of test cases : " << EP_TEST_COUNT << std::endl
        << "Average search nodes : " << floor(average) << std::endl
        << "Success rate         : " << successRate << "%" << std::endl;
}

void EP_SimulatedAnnealing() {
    double average = 0.0;
    int successCount = 0;
    double successRate;
    const int div = 1000;
    for (int i = 0; i < (EP_TEST_COUNT / div); i++) {
        int count = 0;
        EightPuzzle ep;
        bool flag = EightPuzzle::SimulatedAnnealing(ep, count);
        average += (count + 0.0);
        if (flag) {
            successCount++;
        }
        /*
        std::cout << (i + 1) << ": Search nodes : " << (count * 4) << ". ";
        std::cout << (flag ? ("Success, result is : ") : ("Fail, end node is : "));
        std::cout << ep << std::endl;
        */
    }
    average = average / (EP_TEST_COUNT / div);
    successRate = ((successCount + 0.0) / (EP_TEST_COUNT / div)) * 100.0;
    std::cout << std::endl << "Simulated Annealing:" << std::endl;
    std::cout << "Amount of test cases  : " << (EP_TEST_COUNT / div) << std::endl
        << "Average search states : " << floor(average) << std::endl
        << "Success rate          : " << successRate << "%" << std::endl;
}

int main() {
    srand(time(NULL));
    /*
     * 由于8皇后每个状态都有56种可能情况, 因此最终的nodes是状态数*56
     * 退火搜索的节点数多, 结果也大, 因此不输出node而输出state数
     */
    std::cout << "8-Queens Problem : " << std::endl;
    EQ_HillClimbingSA();
    EQ_HillClimbingFC();
    EQ_SimulatedAnnealing();
    /* 8数码输出与8皇后类似 */
    std::cout << std::endl << "8-Puzzle Problem : " << std::endl;
    EP_HillClimbingSA();
    EP_HillClimbingFC();
    EP_SimulatedAnnealing();
    return 0;
}
