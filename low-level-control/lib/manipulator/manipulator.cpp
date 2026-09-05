#include "manipulator.hpp"

//==================================================
// Servo Objects
//==================================================

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist;

//==================================================
// Current Angles
//==================================================

static int baseAngle = 65;
static int shoulderAngle = 90;
static int elbowAngle = 90;
static int wristAngle = 90;

//==================================================
// Step Size
//==================================================

static int step = 5;


static int clampServo(int angle)
{
    if (angle < 0)
        return 0;

    if (angle > 180)
        return 180;

    return angle;
}

//==================================================

static void updateRobot()
{
    baseAngle = clampServo(baseAngle);
    shoulderAngle = clampServo(shoulderAngle);
    elbowAngle = clampServo(elbowAngle);
    wristAngle = clampServo(wristAngle);

    base.write(baseAngle);
    shoulder.write(shoulderAngle);
    elbow.write(elbowAngle);
    wrist.write(wristAngle);
}

//==================================================

static void setPose(
    int newBase,
    int newShoulder,
    int newElbow,
    int newWrist
)
{
    while (
        baseAngle != newBase ||
        shoulderAngle != newShoulder ||
        elbowAngle != newElbow ||
        wristAngle != newWrist
    )
    {
        if (baseAngle < newBase) baseAngle++;
        else if (baseAngle > newBase) baseAngle--;

        if (shoulderAngle < newShoulder) shoulderAngle++;
        else if (shoulderAngle > newShoulder) shoulderAngle--;

        if (elbowAngle < newElbow) elbowAngle++;
        else if (elbowAngle > newElbow) elbowAngle--;

        if (wristAngle < newWrist) wristAngle++;
        else if (wristAngle > newWrist) wristAngle--;

        updateRobot();

        delay(15);   // Increase for slower motion
    }
}

//==================================================

void manipulatorBegin()
{
    base.attach(PB10);
    shoulder.attach(PB9);
    elbow.attach(PB8);
    wrist.attach(PA6);

    home();

    Serial.println("Manipulator Ready");
}

//==================================================

void home()
{
    setPose(
        65,  // Base
        90,  // Shoulder
        90,  // Elbow
        90   // Wrist
    );

    Serial.println("Manipulator Home");
}

//==================================================

void printPose()
{
    Serial.println();

    Serial.print("Base: ");
    Serial.println(baseAngle);

    Serial.print("Shoulder: ");
    Serial.println(shoulderAngle);

    Serial.print("Elbow: ");
    Serial.println(elbowAngle);

    Serial.print("Wrist: ");
    Serial.println(wristAngle);
}

//==================================================

static void preset1()
{
    setPose(
        65,   // Base
        160,  // Shoulder
        150,  // Elbow
        160   // Wrist
    );

    Serial.println("Preset 1");
}

//==================================================

static void preset2()
{
    setPose(
        65,   // Base
        0,    // Shoulder
        100,  // Elbow
        50    // Wrist
    );

    Serial.println("Preset 2");
}

//==================================================

static void preset3()
{
    setPose(
        65,   // Base
        20,   // Shoulder
        180,  // Elbow
        90    // Wrist
    );

    Serial.println("Preset 3");
}

//==================================================

static void preset4()
{
    setPose(
        65,   // Base
        90,   // Shoulder
        90,   // Elbow
        155   // Wrist
    );

    Serial.println("Preset 4");
}

//==================================================

static void preset5()
{
    setPose(
        65,   // Base
        85,   // Shoulder
        90,   // Elbow
        120   // Wrist
    );

    Serial.println("Preset 5");
}

//==================================================

static void preset6()
{
    setPose(
        65,   // Base
        180,  // Shoulder
        180,  // Elbow
        90    // Wrist
    );

    Serial.println("Preset 6");
}

void manipulatorCommand(char cmd)
{
    cmd = toupper(cmd);

    switch (cmd)
    {
        // Base
        case 'L':
            baseAngle += step;
            break;

        case 'O':
            baseAngle -= step;
            break;

        // Shoulder
        case 'Y':
            shoulderAngle += step;
            break;

        case 'H':
            shoulderAngle -= step;
            break;

        // Elbow
        case 'J':
            elbowAngle += step;
            break;

        case 'U':
            elbowAngle -= step;
            break;

        // Wrist
        case 'K':
            wristAngle += step;
            break;

        case 'I':
            wristAngle -= step;
            break;

        // Home
        case 'N':
            home();
            return;

        // Print current pose
        case 'P':
            printPose();
            return;

        // Fixed presets
        case '1':
            preset1();
            return;

        case '2':
            preset2();
            return;

        case '3':
            preset3();
            return;

        case '4':
            preset4();
            return;

        case '5':
            preset5();
            return;
        
        case '6':
            preset6();
            return;

        default:
            return;
        

    }

    updateRobot();
}