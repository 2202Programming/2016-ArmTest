#include "WPILib.h"
#include "IControl.h"
#include "NewXboxController.h"
#include "ArmControl.h"

#define CONTROLLERS 2

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	IControl* controllers[CONTROLLERS];

	void RobotInit()
	{
		for (int i = 0; i < CONTROLLERS; i++) {
			controllers[i] = NULL;
		}

		controllers[0] = NewXboxController::getInstance();
		controllers[1] = new ArmControl();
	}

	void AutonomousInit()
	{
	}

	void AutonomousPeriodic()
	{
	}

	void TeleopInit()
	{
		for (int i = 0; i < CONTROLLERS; i++) {
			controllers[i]->TeleopInit();
		}
	}

	void TeleopPeriodic()
	{
		for (int i = 0; i < CONTROLLERS; i++) {
			controllers[i]->TeleopPeriodic();
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
