//Use multiple inertial sensors
class MultiIMU{
    private:
        pros::Imu imu_one;
        pros::Imu imu_two;
        pros::Imu imu_three;
    public:
        MultiIMU(int port_one,int port_two,int port_three);
        void calibrate();
        void reset();
        float one_data_point(float value_one, float value_two, float value_three);
        float get_rotation();
        float get_heading();
        void tare_rotation();
        void tare_heading();
        void set_heading(int heading);
        void set_rotation(int rotation);

};

//PID Loops for Drivetrain
class DrivePID{
    private:
        //Forward & Backward
        double kp_fb;
        double ki_fb;
        double kd_fb;
        //Turn
        double kp_tu;
        double ki_tu;
        double kd_tu;

        //General
        bool finish;
        double breakpoint;
        double minimum;
        int dt;
        double target;
        bool turn;
        std::uint32_t time;

        //Loop
        double l_encode;
        double r_encode;
        double l_error;
        double r_error;
        double lp;
        double rp;
        double li;
        double ri;
        double loe;
        double roe;
        double ld;
        double rd;
        double l_add;
        double r_add;
        double l_motor;
        double r_motor;
        double kp;
        double ki;
        double kd;
        int t;
        //R
        int settle;
        int s;
        //R

        void hmove(double distance);
        void hturn(double angle);

    public:
        bool is_finished();
        DrivePID(double kp_fb,double ki_fb,double kd_fb, double kp_tu,double ki_tu,double kd_tu, double dt=20);
        void prepare(double distangle, bool turn=0, bool rev=0);
        void go();
        void timeout(int t);
        void q_go(double distangle, bool turn=0, int wait=0);
};

//Smart Controller Printing
class SmartCon{
    private:
    std::string first_check;
    std::string second_check;
    std::string third_check;
    std::string return_string;
    int return_num;
    int line;
    bool debug;
    int raw_ticks;
    int raw_sec;
    int total_time;
    int return_min;
    int return_sec;
    public:
    SmartCon(int total_time);
    std::tuple<int,std::string> print(std::string line_one, std::string line_two, std::string line_three, std::string rumble, std::tuple<int,int,int> order); 
    std::string get_time();
};


//Pneumatics Wrapper
class PneumaticsWrapper{
    private:
        int adi_port;
        int smart_port;
        bool current_state;
        enum pneu_states{
            off = 0,
            disabled = 0,
            retracted = 0,
            on = 1,
            enabled = 1,
            expanded = 1,
        };
    public:
        PneumaticsWrapper(int adi_port, int smart_port = 22);
        //This requires a function overload because you can't
        //have an int (really a real bool) as the name part of an enum
        bool set_value(pneu_states possibilities);
        bool set_value(bool possibilities);
        bool swap_state();      
};