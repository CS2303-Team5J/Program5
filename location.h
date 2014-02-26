#ifndef LOCATION_H
#define LOCATION_H


class location
{
    public:
        location();
        virtual ~location();
        int GetxCoord() { return xCoord; }
        void SetxCoord(int val) { xCoord = val; }
        int GetyCoord() { return yCoord; }
        void SetyCoord(int val) { yCoord = val; }
    private:
        int xCoord;
        int yCoord;
};

#endif // LOCATION_H
