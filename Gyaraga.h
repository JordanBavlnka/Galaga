#ifndef GYARAGA_H
#define GYARAGA_H


class Gyaraga: public Ship
{
    public:
        Gyaraga();
        virtual ~Gyaraga();
        void move(bool);
        void addShip();
        void caught();

    protected:

    private:
        bool together;
};

#endif // GYARAGA_H
