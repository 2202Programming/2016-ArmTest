/*
 * ArmControl.h
 *
 *  Created on: Jan 16, 2016
 *      Author: danielowen
 */

#include "WPILib.h"
#include "NewXboxController.h"
#include "IControl.h"

#ifndef SRC_ARMCONTROL_H_
#define SRC_ARMCONTROL_H_

class ArmControl: public IControl {
public:

	void RobotInit();
	void TeleopInit();
	void TeleopPeriodic();
	ArmControl();

private:
	DoubleSolenoid *pistonL;
	DoubleSolenoid *pistonR;
	Talon* motorL;
	Talon* motorR;
	Compressor *compressor;
	NewXboxController *xbox;

	bool isPistonExtended;
	double motorOutput;

	virtual ~ArmControl();

	void initialize();
	void compressorEnable();
	void compressorDisable();
	void ballGrabberExtend();
	void ballGrabberRetract();
	bool ballGrabberIsExtended();

	void ballGrabberToggle() {
			if (isPistonExtended) {
				ballGrabberRetract();
			} else {
				ballGrabberExtend();
			}
		}

	void ballIn();
	void ballOut();
	void ballStop();
	void motorUpdate();
};

#endif /* SRC_ARMCONTROL_H_ */
