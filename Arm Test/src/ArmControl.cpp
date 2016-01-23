/*
 * ArmControl.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: danielowen
 */

#include <ArmControl.h>

#define RETRACTTIME 1.0
#define SOLENOIDCOMPONENT 2
#define LG_A 0
#define LG_B 1
#define RG_A 2
#define RG_B 3
#define BGLIMITSWITCH 4

#define BALLGRABBERMOTOR 5
#define THROWERMOTOR 3
#define BALLMOTORSPEED 0.5

ArmControl::ArmControl() {
	xbox = NewXboxController::getInstance();
	compressor = new Compressor(5);
	pistonL = new DoubleSolenoid(LG_A, LG_B);
	//pistonR = new DoubleSolenoid(SOLENOIDCOMPONENT, RG_A, RG_B);
	grabberMotor = new Talon(BALLGRABBERMOTOR);
	throwerMotor= new Talon(THROWERMOTOR);
	isPistonExtended = false; //true if piston is extended
	motorOutput = 0;
	motorOutput2 = 0;

}

void ArmControl::initialize() {
	// the solenoid shuts itself off automatically at about 120 psi so we do not have to shut it off for safety reasons.
	compressor->Start();
	this->ballGrabberRetract();
}

bool ArmControl::ballGrabberIsExtended() {
	return isPistonExtended;
}

void ArmControl::ballGrabberExtend() {
	isPistonExtended = true;
	pistonL->Set(DoubleSolenoid::kReverse);
	//pistonR->Set(DoubleSolenoid::kReverse);
}

void ArmControl::ballGrabberRetract() {
	isPistonExtended = false;
	pistonL->Set(DoubleSolenoid::kForward);
	//pistonR->Set(DoubleSolenoid::kForward);
}

void ArmControl::ballIn() {
	motorOutput = BALLMOTORSPEED;
}

void ArmControl::ballOut() {
	motorOutput = -BALLMOTORSPEED;
}

void ArmControl::ballStop() {
	motorOutput = 0;
}

void ArmControl::throwerOut() {
	motorOutput2 = 1;
}

void ArmControl::throwerIn() {
	motorOutput2 = -1;
}

void ArmControl::throwerStop() {
	motorOutput2 = 0;
}

void ArmControl::motorUpdate() {
	grabberMotor->Set(motorOutput);
	throwerMotor->Set(motorOutput2);
}

ArmControl::~ArmControl() {}

void ArmControl::RobotInit() {
	ArmControl();
}

void ArmControl::TeleopInit() {
	initialize();
}

void ArmControl::TeleopPeriodic() {
	if (xbox->isAPressed()) {
		ballGrabberToggle();
	}

	if (xbox->isBHeld()) {
		ballIn();
	} else if (xbox->isXHeld()) {
		ballOut();
	} else {
		ballStop();
	}

	if (xbox->isRBumperHeld()) {
		throwerIn();
	} else if (xbox->isLBumperHeld()) {
		throwerOut();
	} else {
		throwerStop();
	}

	motorUpdate();
}

