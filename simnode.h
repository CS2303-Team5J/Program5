namespace EIN_JRW_Prog5
{
    class SimNode
    {
        public:
            int getID();
            location getLocation();
            void setLocation(location l);
        protected:
            int nodeID;
            location nodeLoc;

    };
}
