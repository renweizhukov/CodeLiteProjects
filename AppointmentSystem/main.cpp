#include <iostream>
#include "AppointmentSystem.h"



int main()
{
    AppointmentSystem app;
    app.Reserve(800, 830);
    app.Reserve(1200, 1300);
    app.Reserve(1400, 1600);
    
    cout << std::boolalpha;
    cout << "IsAvailable(1200, 1230) = " << app.IsAvailable(1200, 1230) << endl;
    cout << "IsAvailable(700, 800) = " << app.IsAvailable(700, 800) << endl;
    
    app.Release(800, 900);
    cout << "IsAvailable(800, 900) = " << app.IsAvailable(700, 800) << endl;
    
    app.Release(1200, 1600);
    cout << "IsAvailable(1200, 1600) = " << app.IsAvailable(1200, 1600) << endl;
    
	return 0;
}