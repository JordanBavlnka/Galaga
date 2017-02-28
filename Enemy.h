#pragma once
class Enemy
{
public:
        Enemy();
        void dive();
        void idle();
        void goAlongPath();
private:
        bool canIdle;
        vector<int[2]>* curPath();
        int home[2];
};
